#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.hpp"
#ifdef _WIN32
#include "SDL_image.h"
#else 
#include "SDL2/SDL_image.h"
#endif

class TextureManager{
	public:
		static SDL_Texture* LoadTexture(const char* fileName);
		static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip);

};

#endif
