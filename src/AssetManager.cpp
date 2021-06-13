#include "AssetManager.hpp"
#include "Game.hpp"

AssetManager::AssetManager(EntityManager* manager){
    this->entityManager = manager;
}
AssetManager::~AssetManager(){}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {

    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return textures[textureId];
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize){
    fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId){
    return fonts[fontId];
}

/*
void CreateTilemap(std::string textureId, std::string tilemapId, int tileSize, int margin = 0)
{
    Tilemap* newTilemap = new Tilemap(tilemapId, textureId, tileSize, margin);

    tilemaps.emplace(newTilemap);

    return this->tilemaps[tilemapId];
}

Tilemap* AssetManager::GetTilemap(std::string tilemapId)
{
    return this->tilemaps[tilemapId]
}
*/