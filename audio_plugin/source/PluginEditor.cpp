namespace audio_plugin {
PluginEditor::PluginEditor(PluginProcessor& p)
    :
AudioProcessorEditor(&p),
//gainAttachment(p.getParameterRefs().gain, gainSlider),
//gainButtonAttachment(p.getParameterRefs().gainButton, gainButton),
//frequencyAttachment(p.getParameterRefs().frequency, frequencySlider),
//frequencyButtonAttachment(p.getParameterRefs().frequencyButton, frequencyButton),
//waveformAttachment(p.getParameterRefs().waveform, waveformBox),
processorRef(p){

  juce::ignoreUnused(processorRef);

//  gainSlider.setRange(0.f, 0.25f, 0.01f);
//  gainSlider.setValue(0.12f);
  gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
  gainLabel.setText("Noise", juce::dontSendNotification);
  gainButton.onClick = [this]() {
    gainButton.setButtonText("");
  };
  gainButton.onClick();

//  frequencySlider.setRange(50.f,500.f, 0.01f);
//  frequencySlider.setValue(200.f);
  frequencySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
  frequencyLabel.setText("Frequency", juce::dontSendNotification);
  frequencyButton.onClick = [this]() {
    frequencyButton.setButtonText("");
  };
  frequencyButton.onClick();

  //waveformBox.addItemList(p.getParameterRefs().waveform.choices, 1);
  waveformBox.addItem("Sine",1);
  waveformBox.addItem("Sawtooth",2);
  waveformBox.addItem("Square",3);
  waveformBox.setSelectedId(1);

  loadButton.onClick =  [this](){
    DBG("clicked");
    fileChooser = std::make_unique<juce::FileChooser>("Select sample",
                                            juce::File {},
                                            "*.wav;*.mp3"
                                          );

    auto flags = juce::FileBrowserComponent::openMode
                 | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(flags,
                        [this](const juce::FileChooser& fc){
                            auto file = fc.getResult();

                            if (file.existsAsFile()){
                                bool loaded = processorRef.loadSample(file);
                                if(loaded){
                                  processorRef.getSampleSource().restart();
                                }
                                loadLabel.setText(loaded ? file.getFileName(): "Failed to load", juce::dontSendNotification);
                            }

                            fileChooser.reset();
                        });
  };
  sampleLevelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
  sampleLevelLabel.setText("Sample Level", juce::dontSendNotification);
  sampleSpeedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
  sampleSpeedLabel.setText("Sample Speed", juce::dontSendNotification);
  sampleSpeedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
  sampleSpeedLabel.setText("Sample Speed", juce::dontSendNotification);

  addAndMakeVisible(gainSlider);
  addAndMakeVisible(gainLabel);
  addAndMakeVisible(gainButton);
  addAndMakeVisible(frequencySlider);
  addAndMakeVisible(frequencyLabel);
  addAndMakeVisible(frequencyButton);
  addAndMakeVisible(waveformBox);
  addAndMakeVisible(waveformLabel);
  addAndMakeVisible(loadButton);
  addAndMakeVisible(loadLabel);
  addAndMakeVisible(sampleLevelSlider);
  addAndMakeVisible(sampleLevelLabel);
  addAndMakeVisible(sampleSpeedSlider);
  addAndMakeVisible(sampleSpeedLabel);
  addAndMakeVisible(sampleLoopButton);

  gainAttachment = std::make_unique<SliderAttachment>(processorRef.apvts, "gain", gainSlider);
  gainButtonAttachment = std::make_unique<ButtonAttachment>(processorRef.apvts, "gainButton", gainButton);
  frequencyAttachment = std::make_unique<SliderAttachment>(processorRef.apvts, "frequency", frequencySlider);
  frequencyButtonAttachment = std::make_unique<ButtonAttachment>(processorRef.apvts, "frequencyButton", frequencyButton);
  waveformAttachment = std::make_unique<ComboBoxAttachment>(processorRef.apvts, "waveform", waveformBox);
  sampleLevelAttachment = std::make_unique<SliderAttachment>(processorRef.apvts, "sampleLevel", sampleLevelSlider);
  sampleSpeedAttachment = std::make_unique<SliderAttachment>(processorRef.apvts, "sampleSpeed", sampleSpeedSlider);
  sampleLoopAttachment = std::make_unique<ButtonAttachment>(processorRef.apvts, "sampleLoop", sampleLoopButton);

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

  loadLabel.setBounds(40, 70, getWidth() - 100, 20);
  loadButton.setBounds(getWidth() - 100, 70, 80, 20);
  sampleLevelSlider.setBounds(150, 100, getWidth() - 170, 20);
  sampleLevelLabel.setBounds(40, 100, 100, 20);
  sampleSpeedSlider.setBounds(150, 130, getWidth() - 170, 20);
  sampleSpeedLabel.setBounds(40, 130, 100, 20);
  sampleLoopButton.setBounds(40, 160, 100, 20);
}
}  // namespace audio_plugin
