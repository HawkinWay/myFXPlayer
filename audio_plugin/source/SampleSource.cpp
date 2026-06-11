namespace audio_plugin{
SampleSource::SampleSource() {
  formatManager.registerBasicFormats();
}

bool SampleSource::loadFile(const juce::File& file) {
  if (file == juce::File{}) {
    return false;
  }
  const std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
  if (reader == nullptr) {
    return false;
  }

  sampleBuffer.setSize(static_cast<int>(reader->numChannels),
                       static_cast<int>(reader->lengthInSamples));

  reader->read(&sampleBuffer,
               0,
               static_cast<int>(reader->lengthInSamples),
               0,
               true,
               true);

  readPosition = 0.0;

  return true;
}

void SampleSource::process(juce::AudioBuffer<float>& buffer) {
  const int numSampleSamples = sampleBuffer.getNumSamples();

  if (numSampleSamples == 0) {
    return;
  }

  const int numOutputChannels = buffer.getNumChannels();
  const int numOutputSamples = buffer.getNumSamples();
  const int numSampleChannels = sampleBuffer.getNumChannels();

  for (int sampleIdx = 0; sampleIdx < numOutputSamples; ++sampleIdx){
    int posIdx = static_cast<int>(readPosition);
    float fractionalPart = static_cast<float>(readPosition - posIdx);

    if (posIdx >= numSampleSamples - 1) {
      if (loop){
        readPosition = 0.0;
        posIdx = 0;
      }
      else{
        for (int ch = 0; ch < numOutputChannels; ++ch)
          buffer.getWritePointer(ch)[sampleIdx] = 0.0f;
        continue;
      }
    }

    int nextPosIdx = (posIdx + 1) % numSampleSamples;

    for (int ch = 0; ch < numOutputChannels; ++ch)
    {
      int sourceChannel = std::min(ch, numSampleChannels - 1);
      auto* data = buffer.getWritePointer(ch);

      float sample1 = sampleBuffer.getReadPointer(sourceChannel)[posIdx];
      float sample2 = sampleBuffer.getReadPointer(sourceChannel)[nextPosIdx];

      float interpolatedSample = sample1 + fractionalPart * (sample2 - sample1);
      data[sampleIdx] += sample * level;
    }

    readPosition += speed;
  }
}

void SampleSource::setLevel(float newLevel){
  level = juce::jlimit(0.f, 1.f, newLevel);
}

void SampleSource::setSpeed(float newSpeed) {
  speed = newSpeed;
}

void SampleSource::setLoop(bool shouldLoop) {
  loop = shouldLoop;
}

void SampleSource::stop() {
  readPosition = sampleBuffer.getNumSamples();
}

void SampleSource::restart() {
  readPosition = 0.0;
}

bool SampleSource::isLoaded(){
  return sampleBuffer.getNumSamples() > 0;
}
}