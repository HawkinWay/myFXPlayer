namespace audio_plugin {
juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout() {
  juce::AudioProcessorValueTreeState::ParameterLayout layout;

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{"gain", 1}, "Gain", juce::NormalisableRange<float>(0.0f, 0.25f, 0.01f), 0.12f));

  layout.add(std::make_unique<juce::AudioParameterBool>(
      juce::ParameterID{"gainButton", 1}, "Gain Button", false));

  layout.add(std::make_unique<juce::AudioParameterChoice>(
      juce::ParameterID{"waveform", 1}, "Waveform", juce::StringArray{"Sine", "Sawtooth", "Square"}, 0));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{"frequency", 1}, "Frequency", juce::NormalisableRange<float>(50.0f, 500.0f, 0.01f), 200.0f));

  layout.add(std::make_unique<juce::AudioParameterBool>(
      juce::ParameterID{"frequencyButton", 1}, "Frequency Button", false));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{"sampleLevel", 1}, "Sample Level", juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.5f));

  layout.add(std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{"sampleSpeed", 1}, "Sample Speed", juce::NormalisableRange<float>(0.25f, 2.f ,0.01f), 1.f));

  layout.add(std::make_unique<juce::AudioParameterBool>(
      juce::ParameterID{"sampleLoop", 1}, "Sample Loop", true));

  return layout;
}

PluginProcessor::PluginProcessor()
    : AudioProcessor(
          BusesProperties()
#if !JUCE_IS_MIDI_EFFECT
#if !JUCE_IS_SYNTH
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
      ),apvts(*this, nullptr, "Parameters", createParameterLayout()) {
}

const juce::String PluginProcessor::getName() const {
  return JUCE_PLUGIN_NAME;
}

bool PluginProcessor::acceptsMidi() const {
#if JUCE_NEEDS_MIDI_INPUT
  return true;
#else
  return false;
#endif
}

bool PluginProcessor::producesMidi() const {
#if JUCE_NEEDS_MIDI_OUTPUT
  return true;
#else
  return false;
#endif
}

bool PluginProcessor::isMidiEffect() const {
#if JUCE_IS_MIDI_EFFECT
  return true;
#else
  return false;
#endif
}

double PluginProcessor::getTailLengthSeconds() const {
  return 0.0;
}

int PluginProcessor::getNumPrograms() {
  return 1;  // NB: some hosts don't cope very well if you tell them there are 0
             // programs, so this should be at least 1, even if you're not
             // really implementing programs.
}

int PluginProcessor::getCurrentProgram() {
  return 0;
}

void PluginProcessor::setCurrentProgram(int index) {
  juce::ignoreUnused(index);
}

const juce::String PluginProcessor::getProgramName(int index) {
  juce::ignoreUnused(index);
  return {};
}

void PluginProcessor::changeProgramName(int index,
                                        const juce::String& newName) {
  juce::ignoreUnused(index, newName);
}

void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  juce::ignoreUnused(sampleRate, samplesPerBlock);
  noise.prepare(sampleRate, samplesPerBlock);
  waveformSynth.prepare(sampleRate, samplesPerBlock);
}

void PluginProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
#if JUCE_IS_MIDI_EFFECT
  juce::ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

  // This checks if the input layout matches the output layout
#if !JUCE_IS_SYNTH
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}

void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                   juce::MidiBuffer& midiMessages) {
  juce::ignoreUnused(midiMessages);

  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());


  // float currentGain = parameters.gain.get();
  float currentGain = apvts.getRawParameterValue("gain")->load();
  // auto NoiseButton = parameters.gainButton.get();
  bool NoiseButton = apvts.getRawParameterValue("gainButton")->load() > 0.5f;
  if (!NoiseButton) {
    currentGain = 0.f;
  }
  noise.process(buffer,currentGain);

//  int waveformIndex = parameters.waveform.getIndex();
//  float currentFrequency = parameters.frequency.get();
//  auto FrequencyButton = parameters.frequencyButton.get();
  float currentFreq = apvts.getRawParameterValue("frequency")->load();
  bool freqButton = apvts.getRawParameterValue("frequencyButton")->load() > 0.5f;
  int waveformType = static_cast<int>(apvts.getRawParameterValue("waveform")->load());
  if (!freqButton) {
    currentFreq = 0.f;
  }
  waveformSynth.setWaveformType(static_cast<WaveformSynth::WaveformType>(waveformType));
  waveformSynth.process(buffer, currentFreq);

  if(sampleSource.isLoaded()){
    float sampleLevel = apvts.getRawParameterValue("sampleLevel")->load();
    float sampleSpeed = apvts.getRawParameterValue("sampleSpeed")->load();
    bool sampleLoop = apvts.getRawParameterValue("sampleLoop")->load() > 0.5f;

    sampleSource.setLevel(sampleLevel);
    sampleSource.setSpeed(sampleSpeed);
    sampleSource.setLoop(sampleLoop);
    sampleSource.process(buffer);
  }

  // This is the place where you'd normally do the guts of your plugin's
  // audio processing...
  // Make sure to reset the state if your inner loop is processing
  // the samples and the outer loop is handling the channels.
  // Alternatively, you can process the samples with the channels
  // interleaved by keeping the same state.
//  for (int channel = 0; channel < totalNumInputChannels; ++channel) {
//    auto* channelData = buffer.getWritePointer(channel);
//    juce::ignoreUnused(channelData);
//    // ..do something to the data...
//    for (auto sample = 0; sample < buffer.getNumSamples(); sample++) {
//      //channelData[sample] *= currentGain;
//    }
//  }
}

bool PluginProcessor::hasEditor() const {
  return true;  // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginProcessor::createEditor() {
  return new PluginEditor(*this);
}

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
  juce::ignoreUnused(destData);
}

void PluginProcessor::setStateInformation(const void* data, int sizeInBytes) {
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
  juce::ignoreUnused(data, sizeInBytes);
}
}  // namespace audio_plugin

// This creates new instances of the plugin.
// This function definition must be in the global namespace.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new audio_plugin::PluginProcessor();
}
