#ifndef CBE_AUDIO_OPENAL
#define CBE_AUDIO_OPENAL

#include "Types/Vector2.hpp"
#include "Data/Wave.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <string>

//TODO(fhomolka): AudioListener Component
struct OALListener
{
    CB::Vec2 postion = {0.0f, 0.0f};
};

//TODO(fhomolka): Tie this to some actual source, like audio-source component
struct OALSource
{
    ALuint id;
    CB::Vec2 position = {0.0f, 0.0f};
    ALboolean looping = AL_FALSE;
    ALuint buffer;
    CB::Wave* audioData;
};

class Aud_OpenAL
{
    public:
    Aud_OpenAL(/* args */);
    ~Aud_OpenAL();

    bool BufferAndPlay(CB::Wave* audioData);
    private:
        ALCdevice* audioDevice;
        ALCcontext* audioContext;
        ALCenum alError;

        OALListener listener;
        OALSource source;

        bool alCheckError(std::string errorMsg = "");
        bool alcCheckError(std::string errorMsg = "");

        ALenum getOpenALFormat(CB::Wave* wav);

};

#endif