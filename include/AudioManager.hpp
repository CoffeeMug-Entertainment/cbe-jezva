#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "SDL2/SDL_audio.h"
#ifdef _WIN32 //See Simple-SDL2-Audio's README.md
#define SDL_AUDIO_ALLOW_CHANGES SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE
#endif
#include "audio.h"

class AudioManager
{
    public:
    static Audio* LoadWav(const char* fileName, bool loop = false);
    static void PlayWav(Audio* audioData, float volume = 1.0f);

};

#endif // AUDIOMANAGER_HPP
