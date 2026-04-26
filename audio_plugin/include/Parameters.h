#pragma once

namespace audio_plugin{
struct Parameters {
  explicit  Parameters(juce::AudioProcessor&);
  juce::AudioParameterFloat &gain;
};

}