#include "AssetManager.hpp"
#include "Game.hpp"
#include "FontManager.hpp"
#include <fstream>
#include <sstream>

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

sdl_stb_font_cache* AssetManager::GetFont(std::string fontId){
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

const char* fontsKey = "Fonts";
const char* texturesKey = "Textures";

void AssetManager::LoadFromAssetsJson(const char* filePath)
{
	std::ifstream assetFile(filePath);
	std::string unparsedAssetFileData;

	if (!assetFile)
	{
		Game::logger->LogError("Tried parsing " + std::string(filePath) + " but that doesn't exist!");
		return;
	}

	std::ostringstream ss;
	ss << assetFile.rdbuf();
	unparsedAssetFileData = ss.str();

	nlohmann::json parsedAssetFile = nlohmann::json::parse(unparsedAssetFileData);

	for(const auto& f : parsedAssetFile[fontsKey])
	{
		FontInfo newFont;
		//fhomolka 13/06/2021 13:42
		//HACK: https://github.com/nlohmann/json#arbitrary-types-conversions
		//      It fails when I dod that, so let's do it manually!
		newFont.id = f["id"].get<std::string>();
		newFont.filePath = f["path"].get<std::string>(); //fhomolka 13/06/2021 13:45 apparently, it does not recognize char*
		newFont.size = f["size"].get<int>();

		this->AddFont(newFont.id, newFont.filePath.c_str(), newFont.size);
	}

	for(const auto& f : parsedAssetFile[texturesKey])
	{
		TextureInfo newTexture;
		newTexture.id = f["id"].get<std::string>();
		newTexture.filePath = f["path"].get<std::string>();

		this->AddTexture(newTexture.id, newTexture.filePath.c_str());
	}
}