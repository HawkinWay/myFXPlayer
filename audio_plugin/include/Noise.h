#pragma once

namespace audio_plugin {
class Noise {
public:
  void prepare(double sampleRate, int samplesPerBlock) noexcept{
    juce::ignoreUnused(sampleRate);
    smoothedNoiseGain.reset(sampleRate, 0.02);
  }

  void process(juce::AudioBuffer<float> &buffer, float targetGain) noexcept {
    smoothedNoiseGain.setTargetValue(targetGain);

    for (auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {

      float currenGain = smoothedNoiseGain.getNextValue();

      for (auto channelIndex : std::views::iota(0, buffer.getNumChannels())) {
        auto *data = buffer.getWritePointer(channelIndex);
        float noise = ((random.nextFloat() * 2.f) - 1.f) * currenGain;
        //buffer.setSample(channelIndex,frameIndex,noise);
        data[frameIndex] = noise;
      }
    }
  }

  void release() noexcept {

  }
private:
  juce::Random random;
  juce::LinearSmoothedValue<float> smoothedNoiseGain;
};
}