#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include "Game.hpp"
#include "sdlStbFont.h"
#include "Types/Vector2.hpp"

class FontManager {
   public:
		static sdl_stb_font_cache* LoadFont(const char* fileName, int fontSize);
		static void Draw(sdl_stb_font_cache* font_cache, CB::Vec2 position, std::string text);
		static void Draw(SDL_Texture* texture, CB::Vec2 position, CB::Vec2 size);
};


#endif
