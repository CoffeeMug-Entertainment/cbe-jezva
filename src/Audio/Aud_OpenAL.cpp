#include "Audio/Aud_OpenAL.hpp"
#include "Game.hpp"

Aud_OpenAL::Aud_OpenAL()
{
    const ALCchar* deviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    this->audioDevice = alcOpenDevice(deviceName);
    if(alcCheckError("Failed to get audio device!")) return;

    this->audioContext = alcCreateContext(this->audioDevice, NULL);
    if(alcCheckError("Failed to create audio context!")) return;

    if(!alcMakeContextCurrent(this->audioContext))
    {
        alcCheckError("Failed to make a context into CurrentContext");
        return;
    }

    //TODO(fhomolka): eugh
    alListener3f(AL_POSITION, listener.postion.x, listener.postion.y, 1.0f);
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    ALfloat orientation[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListenerfv(AL_ORIENTATION, orientation);

    alGenSources(1, &source.id);
    alSourcef(source.id, AL_PITCH, 1.0f);
    alSourcef(source.id, AL_GAIN, 1.0f);
    alSource3f(source.id, AL_POSITION, source.position.x, source.position.y, 0.0f);
    alSource3f(source.id, AL_VELOCITY,  0.0f,  0.0f, 0.0f);
    alSourcei(source.id, AL_LOOPING, source.looping);

    alGenBuffers(1, &source.buffer);
    alCheckError("Failed to generate buffer!");
}

Aud_OpenAL::~Aud_OpenAL()
{
    alDeleteSources(1, &source.id);
    alDeleteBuffers(1, &source.buffer);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(this->audioContext);
    alcCloseDevice(this->audioDevice);
}

bool Aud_OpenAL::BufferAndPlay(CB::Wave* audioData)
{
    alBufferData(source.buffer, getOpenALFormat(audioData), audioData->data, audioData->dataSize, audioData->sampleRate);
    alCheckError("Failed to load wave data into buffer!");

    alSourcei(source.id, AL_BUFFER, source.buffer);
    if(alCheckError("Failed to set source for buffer!")) return false;
    
    alSourcePlay(source.id);
    if(alCheckError("Failed to start playing!")) return false;

    return true;
}

bool Aud_OpenAL::alCheckError(std::string errorMsg)
{
    std::string fullMsg = "[OpenAL] " + errorMsg + "\n\tReason: ";
    alError = alGetError();
    if (alError == AL_NO_ERROR) return false;

    switch (alError)
    {
        case AL_INVALID_NAME:
            fullMsg += "AL_INVALID_NAME";
            break;
        case AL_INVALID_ENUM:
            fullMsg += "AL_INVALID_ENUM";
            break;
        case AL_INVALID_VALUE:
            fullMsg +=  "AL_INVALID_VALUE";
            break;
        case AL_INVALID_OPERATION:
            fullMsg += "AL_INVALID_OPERATION";
            break;
        case AL_OUT_OF_MEMORY:
            fullMsg += "AL_OUT_OF_MEMORY";
            break;
        default:
            fullMsg += "Unknown reason!";
            break;
    }

    Game::logger->LogError(fullMsg);

    return true;
}

bool Aud_OpenAL::alcCheckError(std::string errorMsg)
{
    std::string fullMsg = "[OpenAL - alc] " + errorMsg + "\n\tReason: ";
    alError = alcGetError(this->audioDevice);
    if (alError == ALC_NO_ERROR) return false;

    switch (alError)
    {
        case ALC_INVALID_DEVICE:
            fullMsg += "ALC_INVALID_DEVICE";
            break;
        case ALC_INVALID_CONTEXT:
            fullMsg += "ALC_INVALID_CONTEXT";
            break;
        case ALC_INVALID_ENUM:
            fullMsg +=  "ALC_INVALID_ENUM";
            break;
        case ALC_INVALID_VALUE:
            fullMsg += "ALC_INVALID_VALUE";
            break;
        case ALC_OUT_OF_MEMORY:
            fullMsg += "ALC_OUT_OF_MEMORY";
            break;
        default:
            fullMsg += "Unknown reason!";
            break;
    }

    Game::logger->LogError(fullMsg);

    return true;
}

ALenum Aud_OpenAL::getOpenALFormat(CB::Wave* wav)
{
    switch (wav->bitsPerSample)
    {
        case 16:
            if (wav->channels > 1) return AL_FORMAT_STEREO16;
            return AL_FORMAT_MONO16;
            break;
        case 8:
            if (wav->channels > 1) return AL_FORMAT_STEREO8;
            return AL_FORMAT_MONO8;
            break;
        default:
            return -1;
            break;
    }
}