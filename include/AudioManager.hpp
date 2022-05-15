#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "SDL2/SDL_audio.h"

struct AudioData
{
    Uint8* wavBuf;
    Uint32 wavLen;
    SDL_AudioSpec wavSpec;
    SDL_AudioDeviceID wavDevice;
    SDL_AudioSpec recievedSpec;
};

class AudioManager
{
    public:
    static AudioData* LoadWav(const char* fileName);
    static void PlayWav(AudioData* audioData);

};

#endif // AUDIOMANAGER_HPP
