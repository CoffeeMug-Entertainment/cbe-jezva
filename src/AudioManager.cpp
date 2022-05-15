#include "AudioManager.hpp"
#include "Game.hpp"

AudioData* AudioManager::LoadWav(const char* fileName) {
    AudioData* newAudio = new AudioData();
    newAudio->wavBuf = NULL;
    newAudio->wavLen = 0;
    SDL_zero(newAudio->wavSpec);
    SDL_zero(newAudio->wavDevice);
    newAudio->wavSpec.freq = 48000; //HACK(fhomolka): Without this, the frequency goes wack, so let's just default to something sane
    newAudio->wavDevice = SDL_OpenAudioDevice(NULL, SDL_FALSE, &newAudio->wavSpec, &newAudio->recievedSpec, 0);

    auto result = SDL_LoadWAV(fileName, &newAudio->recievedSpec, &newAudio->wavBuf, &newAudio->wavLen);
    if (result == NULL) {
        Game::logger->LogError("Failed to load WAV file: " + std::string(SDL_GetError()));
        return nullptr;
    }

    return newAudio;
}

void AudioManager::PlayWav(AudioData* audioData) {
    SDL_PauseAudioDevice(audioData->wavDevice, SDL_TRUE);
    SDL_ClearQueuedAudio(audioData->wavDevice);
    SDL_QueueAudio(audioData->wavDevice, audioData->wavBuf, audioData->wavLen);
    SDL_PauseAudioDevice(audioData->wavDevice, SDL_FALSE);
}