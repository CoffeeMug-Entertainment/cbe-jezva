#ifndef CB_WAVE_HPP
#define CB_WAVE_HPP

#include "dr_wav.h"

namespace CB
{
    struct Wave
    {
        unsigned int frameCount;
        unsigned int channels;
        unsigned int sampleRate;
        unsigned int bitsPerSample;
        unsigned int dataSize;
        void* data;


        Wave& Clear()
        {
            frameCount = 0;
            channels = 0;
            sampleRate = 0;
            bitsPerSample = 0;
            delete[] static_cast<short*>(data);
            dataSize = 0;

            return *this;
        }

        //TODO(fhomolka): Probably should make this a compile flag
        //#ifdef dr_wav_h


        Wave& FromDRWav(drwav& drWavData)
        {
            this->frameCount = drWavData.totalPCMFrameCount;
            this->sampleRate = drWavData.sampleRate;
            this->bitsPerSample = drWavData.bitsPerSample;
            this->channels = drWavData.channels;
            this->dataSize = this->frameCount * this-> channels * sizeof(short);
            this->data = new short[dataSize];

            drwav_read_pcm_frames_s16(&drWavData, drWavData.totalPCMFrameCount, static_cast<short*>(this->data));

            return *this;
        }

        //#endif
    };
    
}

#endif