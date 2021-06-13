#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include "EntityManager.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
//#include <Data/Tilemap.hpp>

#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

class EntityManager;

class AssetManager {
    public:
        AssetManager(EntityManager *manager);
        ~AssetManager();
        void AddTexture(std::string textureId, const char* filePath);
		SDL_Texture* GetTexture(std::string textureId);
		void AddFont(std::string fontID, const char* filePath, int fontSize);
		TTF_Font* GetFont(std::string fontID);
        //Tilemap* CreateTilemap(std::string textureId, std::string tilemapId, int tileSize, int margin = 0);
        //Tilemap* GetTilemap(std::string tilemapId);
    private:
        EntityManager* entityManager;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
        //std::map<std::string, CB::Tilemap> tilemaps;

};


#endif