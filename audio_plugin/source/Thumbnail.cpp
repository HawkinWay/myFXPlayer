namespace audio_plugin {
Thumbnail::Thumbnail(juce::AudioFormatManager& formatManager) : thumbnail(512, formatManager, cache) {
    thumbnail.addChangeListener(this);
}

void Thumbnail::loadFile(const juce::File& file){
    thumbnail.setSource(new juce::FileInputSource(file));
    repaint();
}

void Thumbnail::setProgress(float newProgress){
    progress = juce::jlimit(0.f, 1.f, newProgress);
    repaint();
}

void Thumbnail::paint(juce::Graphics& g){
    auto area = getLocalBounds();
    if(thumbnail.getTotalLength() <= 0){
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(area);

        g.setColour(juce::Colours::white);
        g.drawFittedText("No file loaded...", area, juce::Justification::centred, 1);
    }else{
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(area);

        g.setColour(juce::Colours::black);
        thumbnail.drawChannels(g, area, 0.0, thumbnail.getTotalLength(), 1.f);
        g.setColour(juce::Colours::red);
        auto position = static_cast<int>(progress * area.getWidth());
        g.drawVerticalLine(position, 0, area.getHeight());
    }
}

void Thumbnail::changeListenerCallback(juce::ChangeBroadcaster* source){
    if(source == &thumbnail){
        repaint();
    }
}
}