#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "SDL2/SDL_audio.h"
#include "audio.h"

class AudioManager
{
    public:
    static Audio* LoadWav(const char* fileName, bool loop = false);
    static void PlayWav(Audio* audioData, float volume = 1.0f);

};

#endif // AUDIOMANAGER_HPP
