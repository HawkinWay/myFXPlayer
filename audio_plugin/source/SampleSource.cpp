#include <tkDecls.h>
namespace audio_plugin{
AudioPlayer::AudioPlayer(){
  formatManager.registerBasicFormats();
}

void AudioPlayer::prepare(double sampleRate, int samplesPerBlock) {
  transportSource.prepareToPlay(samplesPerBlock, sampleRate);
}

void AudioPlayer::loadFile(const juce::File& file) {

}

}