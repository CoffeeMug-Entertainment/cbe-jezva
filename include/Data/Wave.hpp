#ifndef CB_WAVE_HPP
#define CB_WAVE_HPP

namespace CB
{
    struct Wave
    {
        unsigned int frameNum;
        unsigned int channels;
        unsigned int sampleRate;
        unsigned int bitsPerSample;
        char* data;
    };
    
}

#endif