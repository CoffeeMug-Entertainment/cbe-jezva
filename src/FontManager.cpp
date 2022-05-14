#include "FontManager.hpp"
#include "Game.hpp"
#include "Renderers/Ren_SDL.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#define STB_TRUETYPE_INCLUDE_HANDLED
#define SDL_STB_FONT_IMPL
#include "sdlStbFont.h"

sdl_stb_font_cache* FontManager::LoadFont(const char* fileName, int fontSize){

    std::ifstream fontFile(fileName);
    std::ostringstream ss;
    std::string fontData;

    ss << fontFile.rdbuf();
    fontData = ss.str();

    sdl_stb_font_cache* font_cache = new sdl_stb_font_cache();
    font_cache->faceSize = fontSize;
    font_cache->loadFont(fontData.c_str());
    SDL_Renderer* ren = static_cast<Ren_SDL*>(Game::renderer)->Renderer();
    font_cache->bindRenderer(ren);

    return font_cache;
}

void FontManager::Draw(sdl_stb_font_cache* font_cache, CB::Vec2 position, std::string text){
    font_cache->drawText(static_cast<int>(position.x), static_cast<int>(position.y), text);
}

void FontManager::Draw(SDL_Texture* texture, CB::Vec2 position, CB::Vec2 size) {
    SDL_Rect texture_rect;
    texture_rect.x = static_cast<int>(position.x);
    texture_rect.y = static_cast<int>(position.y);
    texture_rect.w = static_cast<int>(size.x);
    texture_rect.h = static_cast<int>(size.y);
    Game::renderer->RenderCopy(texture, texture_rect);
    }