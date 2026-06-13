#pragma once

namespace audio_plugin::ParamIDs{

    // Noise
    inline constexpr auto gain = "gain";
    inline constexpr auto gainButton = "gainButton";

    // WaveformSynth
    inline constexpr auto waveform ="waveform";
    inline constexpr auto frequency = "frequency";
    inline constexpr auto frequencyButton = "frequencyButton";

    // SampleSource
    inline constexpr auto sampleLevel = "sampleLevel";
    inline constexpr auto sampleSpeed = "sampleSpeed";
    inline constexpr auto sampleLoop = "sampleLoop";
    inline constexpr auto sampleEnable = "sampleEnable";
}