#pragma once

namespace audio_plugin{
class Thumbnail : public juce::Component, public juce::ChangeListener {
public:
    explicit Thumbnail(juce::AudioFormatManager& formatManager);
    
    void loadFile(const juce::File& file);

    void setProgress(float newProgress);

    void paint(juce::Graphics& g) override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    
private:
    juce::AudioThumbnailCache cache{5};
    juce::AudioThumbnail thumbnail;

    float progress = 0.f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumbnail)
};
}