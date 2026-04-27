namespace audio_plugin {
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), gainAttachment(p.getPrameterRefs().gain, gainSlider), processorRef(p){
  juce::ignoreUnused(processorRef);

  gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
  gainSlider.setRange(0.f, 1.f, 0.01f);
  //gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
  addAndMakeVisible(gainSlider);

  gainLabel.setText("Gain", juce::dontSendNotification); // 设置显示的文字
  gainLabel.setJustificationType(juce::Justification::centred); // 文字居中
  gainLabel.attachToComponent(&gainSlider, true); // 【核心】将标签绑定到 Slider
  // 第二个参数 false 表示标签在 Slider 的上方；true 表示在左侧
  addAndMakeVisible(gainLabel);

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
  gainSlider.setBounds(getLocalBounds());
  auto bounds = getLocalBounds();
  gainSlider.setBounds(bounds.withSize(300, 40).withCentre(bounds.getCentre()));
}
}  // namespace audio_plugin
