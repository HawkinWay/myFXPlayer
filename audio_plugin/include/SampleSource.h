#pragma once

namespace audio_plugin {
class SampleSource{
public:
  SampleSource();

  bool loadFile(const juce::File& file);

  void process(juce::AudioBuffer<float>& buffer);

  void setSpeed(float newSpeed);

  void setLoop(bool shouldLoop);

  bool isLoaded();

private:
  juce::AudioFormatManager formatManager;
  std::unique_ptr<juce::FileChooser> fileChooser;
  juce::AudioBuffer<float> sampleBuffer;

  double readPosition = 0;
  float level = 0.25f;
  float speed = 1.f;
  bool loop = true;
};
}