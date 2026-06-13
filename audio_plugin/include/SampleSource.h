#pragma once

namespace audio_plugin {
class SampleSource{
public:
  enum class State{
    Empty,
    Stopped,
    Playing
  };

  SampleSource();

  bool loadFile(const juce::File& file);

  void process(juce::AudioBuffer<float>& buffer);

  void setLevel(float newLevel);

  void setSpeed(float newSpeed);

  void setLoop(bool shouldLoop);

  void play();

  void stop();

  void restart();

  bool isLoaded() const;

  float getProgress() const;

private:
  juce::AudioFormatManager formatManager;
  std::unique_ptr<juce::FileChooser> fileChooser;
  juce::AudioBuffer<float> sampleBuffer;

  State state = State::Empty;
  double readPosition = 0;
  float level = 0.25f;
  float speed = 1.f;
  bool loop = true;
};
}