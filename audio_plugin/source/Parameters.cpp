namespace audio_plugin {
namespace {
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

  juce::AudioParameterBool &createGainButtonParameter(juce::AudioProcessor& processor) {
    constexpr auto versionHint = 1;
    auto parameter = std::make_unique<juce::AudioParameterBool>(
      juce::ParameterID{"gainButton",versionHint},
      "Gain Button",
      false
    );
    auto &parameterReference = *parameter;
    processor.addParameter(parameter.release());
    return parameterReference;
  }

  juce::AudioParameterChoice &createWaveformParameter(juce::AudioProcessor& processor){
    constexpr auto versionHint = 1;
    auto parameter = std::make_unique<juce::AudioParameterChoice>(
      juce::ParameterID{"waveform", versionHint},
      "Waveform",
      juce::StringArray{"Sine", "Sawtooth", "Square"},
      0
    );
    auto &parameterReference = *parameter;
    processor.addParameter(parameter.release());
    return parameterReference;
  }

  juce::AudioParameterFloat &createFrequencyParameter(juce::AudioProcessor& processor) {
    constexpr auto versionHint = 1;
    auto parameter = std::make_unique<juce::AudioParameterFloat>(
      juce::ParameterID{"frequency",versionHint},
      "Frequency",
      juce::NormalisableRange<float> { 50.f, 500.f, 0.01f },
      0.5f,
      juce::AudioParameterFloatAttributes{}.withLabel("Hz")
    );
    auto &parameterReference = *parameter;
    processor.addParameter(parameter.release());
    return parameterReference;
  }

  juce::AudioParameterBool &createFrequencybButtonParameter(juce::AudioProcessor& processor){
    constexpr auto versionHint = 1;
    auto parameter = std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{"frequencyButton",versionHint},
        "Frequency Button",
        false
    );
    auto &parameterReference = *parameter;
    processor.addParameter(parameter.release());
    return parameterReference;
  }
}

Parameters::Parameters(juce::AudioProcessor& processor) : 
gain(createGainParameter(processor)),
gainButton(createGainButtonParameter(processor)),
waveform(createWaveformParameter(processor)),
frequency(createFrequencyParameter(processor)),
frequencyButton(createFrequencybButtonParameter(processor)){

}
}  // namespace audio_plugin