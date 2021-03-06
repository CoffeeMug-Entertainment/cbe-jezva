#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "Data/Wave.hpp"

class AudioManager
{
    public:
    static CB::Wave* LoadWave(const char* fileName);
    static void PlayWav(CB::Wave* audioData);

};

#endif // AUDIOMANAGER_HPP
