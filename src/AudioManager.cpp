#include "AudioManager.hpp"
#include "Game.hpp"
#include <algorithm>

Audio* AudioManager::LoadWav(const char* fileName) {
    Audio* newAudio = createAudio(fileName, 0, SDL_MIX_MAXVOLUME);

    if (newAudio == NULL) {
        Game::logger->LogError("Failed to load audio file: " + std::string(SDL_GetError()));
        return nullptr;
    }

    return newAudio;
}

void AudioManager::PlayWav(Audio* audioData, float volume) {
    float realVolume = std::clamp<float>(volume, 0, 1);
    int intVolume = SDL_MIX_MAXVOLUME * realVolume;
    playSoundFromMemory(audioData, intVolume);
}