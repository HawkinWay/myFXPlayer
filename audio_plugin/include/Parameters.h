#pragma once

namespace audio_plugin{
struct Parameters {
  explicit  Parameters(juce::AudioProcessor&);

  juce::AudioParameterFloat &gain;
  juce::AudioParameterBool &gainButton;

  juce::AudioParameterChoice &waveform;
  juce::AudioParameterFloat &frequency;
  juce::AudioParameterBool &frequencyButton;

  JUCE_DECLARE_NON_COPYABLE(Parameters)
};

}