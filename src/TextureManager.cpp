#include "TextureManager.hpp"
#include "Game.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* fileName){
	SDL_Surface* surface = IMG_Load(fileName);

	if (surface == NULL)
	{
		Game::logger->LogError("Unable to load texture " + std::string(fileName) + "\n\t" + std::string(IMG_GetError()));
		return nullptr;
	}

	//SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_Texture* texture = Game::renderer->CreateTextureFromSurface(surface);
	SDL_FreeSurface(surface);
	return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip){
	Game::renderer->RenderCopyEx(texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, flip);
}