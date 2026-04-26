namespace audio_plugin {

juce::AudioParameterFloat &createGainParameter(juce::AudioProcessor& processor) {
  constexpr auto versionHint = 1;
  auto parameter = std::make_unique<juce::AudioParameterFloat>(
    juce::ParameterID{"gain",versionHint},
    "Gain",
    juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f },
    0.5f,
    juce::AudioParameterFloatAttributes{}.withLabel("dB")
  );
  auto &parameterReference = *parameter;
  processor.addParameter(parameter.release());
  return parameterReference;
}

Parameters::Parameters(juce::AudioProcessor& processor) : gain(createGainParameter(processor)) {

}
}  // namespace audio_plugin