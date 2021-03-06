#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include "EntityManager.hpp"
#include "TextureManager.hpp"
//#include "FontManager.hpp"
#include "AudioManager.hpp"
#include "sdlStbFont.h"
#include "nlohmann/json.hpp"
#include "Data/Tilemap.hpp"

#include <map>
#include <string>

class EntityManager;

class AssetManager {
    public:
        AssetManager(EntityManager *manager);
        ~AssetManager();
        void AddTexture(std::string textureId, const char* filePath);
		SDL_Texture* GetTexture(std::string textureId);
		void AddFont(std::string fontId, const char* filePath, int fontSize);
		sdl_stb_font_cache* GetFont(std::string fontId);
        void AddWave(std::string waveId, const char* filePath);
        CB::Wave* GetWave(std::string waveId);
        void LoadFromAssetsJson(const char* filePath);
        void AddTilemap(std::string textureId, std::string tilemapId, int tileSize, int margin = 0);
        CB::Tilemap* GetTilemap(std::string tilemapId);
    private:
        EntityManager* entityManager;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, sdl_stb_font_cache*> fonts;
        std::map<std::string, CB::Wave*> waves;
        std::map<std::string, CB::Tilemap*> tilemaps;
};


struct FontInfo {

    std::string id;
    std::string filePath;
    int size;
};

struct TextureInfo {
    std::string id;
    std::string filePath;
};

struct AudioInfo {
    std::string id;
    std::string filePath;
};

struct TilemapInfo {
    std::string id;
    std::string textureId;
    int tileSize;
    int margin;
};

#endif
