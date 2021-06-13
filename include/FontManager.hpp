#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include "Game.hpp"
#include <SDL2/SDL_ttf.h>

class FontManager {
   public:
		static TTF_Font* LoadFont(const char* fileName, int fontSize);
		static void Draw(SDL_Texture* texture, SDL_Rect position);
};


#endif