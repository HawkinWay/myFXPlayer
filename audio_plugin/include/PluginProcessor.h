#pragma once

namespace audio_plugin {
class PluginProcessor : public juce::AudioProcessor {
public:
  PluginProcessor();

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

  void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
  using AudioProcessor::processBlock;

  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String& newName) override;

  void getStateInformation(juce::MemoryBlock& destData) override;
  void setStateInformation(const void* data, int sizeInBytes) override;

  
//  Parameters& getParameterRefs() noexcept {
//    return parameters;
//  }

  juce::AudioProcessorValueTreeState apvts;

  SampleSource& getSampleSource() noexcept { return sampleSource; }

  bool loadSample(const juce::File& file){ return sampleSource.loadFile(file); }

private:
  // Parameters parameters{*this};    use apvts to replace parameter.h and .cpp
  static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
  Noise noise;
  WaveformSynth waveformSynth;
  SampleSource sampleSource;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
}  // namespace audio_plugin
