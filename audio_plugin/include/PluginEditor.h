#pragma once

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

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
//  juce::SliderParameterAttachment gainAttachment;
//  juce::ButtonParameterAttachment gainButtonAttachment;
  std::unique_ptr<SliderAttachment> gainAttachment;
  std::unique_ptr<ButtonAttachment> gainButtonAttachment;

  juce::Slider frequencySlider;
  juce::Label frequencyLabel{"frequency label", "Frequency"};
  juce::ToggleButton frequencyButton{"Frequency Button"};
  juce::ComboBox waveformBox;
  juce::Label waveformLabel{"waveform label", "Waveform"};
//  juce::SliderParameterAttachment frequencyAttachment;
//  juce::ButtonParameterAttachment frequencyButtonAttachment;
//  juce::ComboBoxParameterAttachment waveformAttachment
  std::unique_ptr<SliderAttachment> frequencyAttachment;
  std::unique_ptr<ButtonAttachment> frequencyButtonAttachment;
  std::unique_ptr<ComboBoxAttachment> waveformAttachment;

  std::unique_ptr<juce::FileChooser> fileChooser;
  juce::TextButton loadButton{"Load Files"};
  juce::Label loadLabel{"Sample File", "No file loaded"};
  juce::Slider sampleLevelSlider;
  juce::Label sampleLevelLabel{"Sample Level", "Sample Level"};
  juce::Slider sampleSpeedSlider;
  juce::Label sampleSpeedLabel{"Sample Speed", "Sample Speed"};
  juce::ToggleButton sampleLoopButton{"Sample Loop Button"};
  std::unique_ptr<SliderAttachment> sampleLevelAttachment;
  std::unique_ptr<SliderAttachment> sampleSpeedAttachment;
  std::unique_ptr<ButtonAttachment> sampleLoopAttachment;

  
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  PluginProcessor& processorRef;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace audio_plugin
