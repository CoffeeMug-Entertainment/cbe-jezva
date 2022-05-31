#include "TextureManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

SDL_Texture* TextureManager::LoadTexture(const char* fileName){

	//TODO(fhomolka): Get some of the data from the coder, like the image format.
	SDL_Surface* surface;
	int img_width, img_height, img_comps;
	unsigned char* img_data = stbi_load(fileName, &img_width, &img_height, &img_comps, STBI_rgb_alpha);

	if (img_data == NULL)
	{
		Game::logger->LogError("Unable to load texture " + std::string(fileName) + "\n\t" + std::string(stbi_failure_reason()));
		surface = SDL_CreateRGBSurfaceWithFormatFrom((void*)MISSING_TEXTURE_IMG.pixel_data, MISSING_TEXTURE_IMG.width, MISSING_TEXTURE_IMG.height, 24, 4 * MISSING_TEXTURE_IMG.width, SDL_PIXELFORMAT_RGB24);
		SDL_Texture* texture = Game::renderer->CreateTextureFromSurface(surface);
		SDL_FreeSurface(surface);
		return texture;
		return nullptr;
	}
	
	surface = SDL_CreateRGBSurfaceWithFormatFrom((void*)img_data, img_width, img_height, 32, 4 * img_width, SDL_PIXELFORMAT_RGBA32);

	if (surface == NULL)
	{
		Game::logger->LogError("Unable to load texture " + std::string(fileName) + "\n\t" + std::string(SDL_GetError()));
		return nullptr;
	}

	//SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_Texture* texture = Game::renderer->CreateTextureFromSurface(surface);
	SDL_FreeSurface(surface);
	stbi_image_free(img_data);
	return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip){
	Game::renderer->RenderCopyEx(texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, flip);
}