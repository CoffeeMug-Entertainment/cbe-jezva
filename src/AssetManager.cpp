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

void AssetManager::AddSFX(std::string sfxId, const char* filePath) {
	sfx.emplace(sfxId, AudioManager::LoadWav(filePath));
}

Audio* AssetManager::GetSFX(std::string sfxId) {
	auto iter = this->sfx.find(sfxId);
	if (iter == sfx.end()) return nullptr;

	return sfx[sfxId];
}

void AssetManager::AddMusic(std::string musicId, const char* filePath){
	music.emplace(musicId, AudioManager::LoadWav(filePath, true));
}

Audio* AssetManager::GetMusic(std::string musicId){
	auto iter = this->music.find(musicId);
	if (iter == music.end()) return nullptr;
	
	return music[musicId];
}

const char* fontsKey = "Fonts";
const char* texturesKey = "Textures";
const char* sfxKey = "SFX";
const char* musicKey = "Music";
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

	for(const auto& f : parsedAssetFile[sfxKey])
	{
		AudioInfo newSFX;
		newSFX.id = f["id"].get<std::string>();
		newSFX.filePath = f["path"].get<std::string>();

		this->AddSFX(newSFX.id, newSFX.filePath.c_str());
	}

	for(const auto& f : parsedAssetFile[musicKey])
	{
		AudioInfo newMusic;
		newMusic.id = f["id"].get<std::string>();
		newMusic.filePath = f["path"].get<std::string>();

		this->AddMusic(newMusic.id, newMusic.filePath.c_str());
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