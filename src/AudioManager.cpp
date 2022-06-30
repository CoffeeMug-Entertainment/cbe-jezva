#include "AudioManager.hpp"
#include "Game.hpp"
#include "Data/Wave.hpp"
#include <algorithm>
#include <fstream>

CB::Wave* LoadWav(const char* fileData, unsigned int fileSize)
{
    CB::Wave* newWav = new CB::Wave();
    drwav wav_as_drwav;

    bool ret = drwav_init_memory(&wav_as_drwav, fileData, fileSize, 0);

    if(!ret)
    {
        Game::logger->LogError("Failed to load WAV file");
        return nullptr;
    }

    newWav->FromDRWav(wav_as_drwav);

    drwav_uninit(&wav_as_drwav);

    return newWav;

}

CB::Wave* AudioManager::LoadWave(const char* fileName) {

    CB::Wave* newWave = nullptr;
    std::ifstream fileStream(fileName, std::ios::binary);
    fileStream.seekg(0, std::ios::end);
    unsigned int fileSize = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);
    
    char first_four_chars[4];
    fileStream.read(first_four_chars, 4);
    fileStream.seekg(0, std::ios::beg);

    if (first_four_chars[0] == 'R' &&
        first_four_chars[1] == 'I' &&
        first_four_chars[2] == 'F' &&
        first_four_chars[3] == 'F'
        )
    {
        Game::logger->Log("Assuming " + std::string(fileName) + " is a Wave file");
        char buffer[fileSize];
        fileStream.read(buffer, fileSize);
        newWave = LoadWav(buffer, fileSize);
    }
    else
    {
        Game::logger->LogError(std::string(fileName) + " is a file of unsupported type!");
    }
    
    fileStream.close();
    return newWave;
}

void AudioManager::PlayWav(CB::Wave* audioData) {

    Game::audioManager->BufferAndPlay(audioData);
}