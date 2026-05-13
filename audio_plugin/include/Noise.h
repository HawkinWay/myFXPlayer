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
#if 0
    for (auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {

      float currenGain = smoothedNoiseGain.getNextValue();

      for (auto channelIndex : std::views::iota(0, buffer.getNumChannels())) {
        auto *data = buffer.getWritePointer(channelIndex);
        const float noise = getRamdomValue() * currenGain;
        //buffer.setSample(channelIndex,frameIndex,noise);
        data[frameIndex] = noise;
      }
    }
#endif

    for (const auto channel : std::views::iota(0, buffer.getNumChannels())) {

      auto* data = buffer.getWritePointer(channel);

      for (const auto sample : std::views::iota(0, buffer.getNumSamples())) {

        const float currentGain = smoothedNoiseGain.getNextValue();
        *data++ = getRamdomValue() * currentGain;
      }

    }
  }

  void release() noexcept {

  }

  float getRamdomValue() noexcept {
    return random.nextFloat() * 2.f - 1.f;
  }

private:
  juce::Random random;
  juce::LinearSmoothedValue<float> smoothedNoiseGain;
};
}