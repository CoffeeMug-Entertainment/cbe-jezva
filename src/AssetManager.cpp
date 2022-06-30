#include "AssetManager.hpp"
#include "Game.hpp"
#include "FontManager.hpp"
#include <fstream>
#include <sstream>

/* GIMP RGB C-Source image */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[2 * 2 * 3 + 1];
} MISSING_TEXTURE_IMG = {
  2, 2, 3,
  "\300\377\356E\040\000E\040\000\300\377\356",
};
const std::string CBE_MISSING_TEXTURE_ID = "CBE_MISSING_TEXTURE";

AssetManager::AssetManager(EntityManager* manager){
	this->entityManager = manager;

	
}

AssetManager::~AssetManager(){}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {

	SDL_Texture* newTex = TextureManager::LoadTexture(filePath);
	if(newTex == nullptr) {
		newTex = GetTexture(CBE_MISSING_TEXTURE_ID);
		if (newTex == nullptr) { //We have not emplaced the 'texture missing' texture yet
			// Add the 'missing texture' texture, to be referenced when a texture can't be found
			SDL_Surface* missingTexSurface = SDL_CreateRGBSurfaceWithFormatFrom((void*)MISSING_TEXTURE_IMG.pixel_data, MISSING_TEXTURE_IMG.width, MISSING_TEXTURE_IMG.height, 24, 4 * MISSING_TEXTURE_IMG.width, SDL_PIXELFORMAT_RGB24);
			SDL_Texture* missingTexTexture = Game::renderer->CreateTextureFromSurface(missingTexSurface);
			SDL_FreeSurface(missingTexSurface);
			textures.emplace(CBE_MISSING_TEXTURE_ID, missingTexTexture);

			newTex = missingTexTexture;
		}
	}
	textures.emplace(textureId, newTex);
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
	auto iter = this->textures.find(textureId);
	if (iter == textures.end()) return nullptr;

	return textures[textureId];
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize){
	fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

sdl_stb_font_cache* AssetManager::GetFont(std::string fontId){
	auto iter = this->fonts.find(fontId);
	if (iter == fonts.end()) return nullptr;

	return fonts[fontId];
}

void AssetManager::AddTilemap(std::string textureId, std::string tilemapId, int tileSize, int margin)
{
	CB::Tilemap* newTilemap = new CB::Tilemap(tilemapId, this->GetTexture(textureId), tileSize, margin);
	tilemaps.emplace(tilemapId, newTilemap);
}

CB::Tilemap* AssetManager::GetTilemap(std::string tilemapId) {
	auto iter = this->tilemaps.find(tilemapId);
	if (iter == tilemaps.end()) return nullptr;

	return this->tilemaps[tilemapId];
}

void AssetManager::AddWave(std::string waveId, const char* filePath) {
	waves.emplace(waveId, AudioManager::LoadWave(filePath));
}

CB::Wave* AssetManager::GetWave(std::string waveId) {
	auto iter = this->waves.find(waveId);
	if (iter == waves.end()) return nullptr;

	return this->waves[waveId];
}

const char* fontsKey = "Fonts";
const char* texturesKey = "Textures";
const char* audioKey = "Audio";
const char* tilemapsKey = "Tilemaps";

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

	for(const auto& f : parsedAssetFile[audioKey])
	{
		AudioInfo newSFX;
		newSFX.id = f["id"].get<std::string>();
		newSFX.filePath = f["path"].get<std::string>();

		this->AddWave(newSFX.id, newSFX.filePath.c_str());
	}

	for(const auto& f : parsedAssetFile[tilemapsKey])
	{
		TilemapInfo newTilemap;
		newTilemap.id = f["id"].get<std::string>();
		newTilemap.textureId = f["texture"].get<std::string>();
		newTilemap.tileSize = f["tile_size"].get<int>();
		newTilemap.margin = f["margin"].get<int>();

		this->AddTilemap(newTilemap.textureId, newTilemap.id, newTilemap.tileSize, newTilemap.margin);
	}
}