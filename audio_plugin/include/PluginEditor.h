#pragma once

namespace audio_plugin {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  juce::Slider gainSlider;
  juce::Label gainLabel{"gain label", "Gain"};
  juce::ToggleButton gainButton{"Gain Button"};
  juce::SliderParameterAttachment gainAttachment;
  juce::ButtonParameterAttachment gainButtonAttachment;

  juce::Slider frequencySlider;
  juce::Label frequencyLabel{"frequency label", "Frequency"};
  juce::ToggleButton frequencyButton{"Frequency Button"};
  juce::ComboBox waveformBox;
  juce::Label waveformLabel{"waveform label", "Waveform"};
  juce::SliderParameterAttachment frequencyAttachment;
  juce::ButtonParameterAttachment frequencyButtonAttachment;
  juce::ComboBoxParameterAttachment waveformAttachment;

  
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  PluginProcessor& processorRef;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace audio_plugin
