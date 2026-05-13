#pragma once

namespace audio_plugin{
struct Parameters {
  explicit  Parameters(juce::AudioProcessor&);

  juce::AudioParameterFloat &gain;

  juce::AudioParameterBool &gainButton;

  JUCE_DECLARE_NON_COPYABLE(Parameters)
};

}