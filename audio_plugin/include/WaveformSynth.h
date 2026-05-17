#pragma once

namespace audio_plugin {
class WaveformSynth {
public:
  enum class WaveformType : size_t {
    sine = 0,
    sawtooth = 1,
    square = 2,
  };

  void prepare(double sampleRate, int samplesPerBlock) noexcept {
    juce::ignoreUnused (samplesPerBlock);
    frequency.reset(sampleRate, 0.02);
    waveformSmoother.reset(sampleRate, 0.02);
    waveformSmoother.setCurrentAndTargetValue(0.f);
    currentSampleRate = sampleRate;
    updateAngleData();
  }

  void process(juce::AudioBuffer<float>& buffer, float targerFrequency) noexcept {
    updateWaveform();

    frequency.setTargetValue(targerFrequency);

    auto level = 0.25f;

    for (const auto sample : std::views::iota(0, buffer.getNumSamples())) {
      updateAngleData();
      const auto currentSample = generateWaveformSample();
      currentAngle += angleDelta;
      if (currentAngle > juce::MathConstants<float>::twoPi) {
        currentAngle -= juce::MathConstants<float>::twoPi;
      }

      for (const auto channel : std::views::iota(0, buffer.getNumChannels())) {

        auto* data = buffer.getWritePointer(channel);
        // data[sample] = currentSample * level;    error, this will cover other audio buffer(like noise)
        data[sample] += currentSample * level;

      }
    }
  }

  void setWaveformType(WaveformType type) noexcept {
    waveformToSet = type;
  }
  
private:
  void updateAngleData() {
    const auto cyclePerSample = frequency.getNextValue() / currentSampleRate;
    angleDelta = cyclePerSample * juce::MathConstants<float>::twoPi;
  }

  void updateWaveform() {
    if (currentWaveform != waveformToSet) {
      currentWaveform = waveformToSet;
    }
  }
  static double sawtooth(double phase) {
    const auto ft = phase / juce::MathConstants<double>::twoPi;
    const auto normalizedPhase = ft - std::floor(ft);
    return normalizedPhase * 2.f - 1.f;
  }

  static double square(double phase) {
    const auto ft = phase / juce::MathConstants<float>::twoPi;
    const auto normalizedPhase = ft - std::floor(ft);
    return (normalizedPhase < 0.5f) ? 1.f : -1.f;
  }

  [[nodiscard]] float generateWaveformSample() const noexcept{
    switch (currentWaveform){
      case WaveformType::sine:
        return static_cast<float>(std::sin(currentAngle));
      case WaveformType::sawtooth:
        return static_cast<float>(sawtooth(currentAngle));
      case WaveformType::square:
        return static_cast<float>(square(currentAngle));
      default:
        return 0.f;
    }
  }

  double currentSampleRate = 0.0;
  double angleDelta = 0.0;
  double currentAngle = 0.0;
  juce::SmoothedValue<float> frequency;
  juce::SmoothedValue<float> waveformSmoother;

  WaveformType currentWaveform = WaveformType::sine;
  WaveformType waveformToSet = currentWaveform;

};
}