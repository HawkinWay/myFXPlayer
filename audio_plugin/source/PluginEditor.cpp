namespace audio_plugin {
PluginEditor::PluginEditor(PluginProcessor& p)
    :
AudioProcessorEditor(&p),
gainAttachment(p.getPrameterRefs().gain, gainSlider),
gainButtonAttachment(p.getPrameterRefs().gainButton, gainButton),
processorRef(p){

  juce::ignoreUnused(processorRef);

  gainSlider.setRange(0.f, 1.f, 0.01f);
  gainSlider.setValue(0.5f);
  gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);

  gainLabel.setText("Gain", juce::dontSendNotification);

  gainButton.onClick = [this]() {
    gainButton.setButtonText("");
  };
  gainButton.onClick();

  addAndMakeVisible(gainSlider);
  addAndMakeVisible(gainLabel);
  addAndMakeVisible(gainButton);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(400, 300);
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
}
}  // namespace audio_plugin
