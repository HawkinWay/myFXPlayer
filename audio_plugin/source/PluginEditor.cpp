namespace audio_plugin {
PluginEditor::PluginEditor(PluginProcessor& p)
    :
AudioProcessorEditor(&p),
gainAttachment(p.getParameterRefs().gain, gainSlider),
gainButtonAttachment(p.getParameterRefs().gainButton, gainButton),
frequencyAttachment(p.getParameterRefs().frequency, frequencySlider),
frequencyButtonAttachment(p.getParameterRefs().frequencyButton, frequencyButton),
waveformAttachment(p.getParameterRefs().waveform, waveformBox),
processorRef(p){

  juce::ignoreUnused(processorRef);

  gainSlider.setRange(0.f, 0.25f, 0.01f);
  gainSlider.setValue(0.12f);
  gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);

  gainLabel.setText("Noise", juce::dontSendNotification);

  gainButton.onClick = [this]() {
    gainButton.setButtonText("");
  };
  gainButton.onClick();

  frequencySlider.setRange(50.f,500.f, 0.01f);
  frequencySlider.setValue(200.f);
  frequencySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);

  frequencyLabel.setText("Frequency", juce::dontSendNotification);

  frequencyButton.onClick = [this]() {
    frequencyButton.setButtonText("");
  };
  frequencyButton.onClick();

  waveformBox.addItemList(p.getParameterRefs().waveform.choices, 1);
  waveformBox.setSelectedId(1);

  addAndMakeVisible(gainSlider);
  addAndMakeVisible(gainLabel);
  addAndMakeVisible(gainButton);
  addAndMakeVisible(frequencySlider);
  addAndMakeVisible(frequencyLabel);
  addAndMakeVisible(frequencyButton);
  addAndMakeVisible(waveformBox);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(600, 500);
}

void PluginEditor::paint(juce::Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(
      getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

  // g.setColour(juce::Colours::white);
  // g.setFont(15.0f);
  // g.drawFittedText("Hello World!", getLocalBounds(),
  //                  juce::Justification::centred, 1);

}

void PluginEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  gainSlider.setBounds(80, 10, getWidth() - 100, 20);
  gainLabel.setBounds(40, 10, 40, 20);
  gainButton.setBounds(10, 10, 50, 20);

  frequencySlider.setBounds(140, 40, getWidth() - 160, 20);
  frequencyLabel.setBounds(40, 40, 40, 20);
  frequencyButton.setBounds(10, 40, 50, 20);
  waveformBox.setBounds(40, 40, 100, 20);
}
}  // namespace audio_plugin
