#include "AudioManager.hpp"
#include "Game.hpp"
#include <algorithm>

Audio* AudioManager::LoadWav(const char* fileName, bool loop) {

    int compatLoopBool = loop ? 1 : 0;
    Audio* newAudio = createAudio(fileName, compatLoopBool, SDL_MIX_MAXVOLUME);

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