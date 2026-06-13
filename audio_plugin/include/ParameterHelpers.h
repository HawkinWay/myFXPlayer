#pragma once

namespace audio_plugin {
    inline float getFloat(juce::AudioProcessorValueTreeState& apvts, const juce::String& id){
        return apvts.getRawParameterValue(id)->load();
    }

    inline bool getBool(juce::AudioProcessorValueTreeState& apvts, const juce::String& id){
        return apvts.getRawParameterValue(id)->load() > 0.5f;
    }

    inline int getChoice(juce::AudioProcessorValueTreeState& apvts, const juce::String& id){
        return static_cast<int>(getFloat(apvts, id));
    }
}