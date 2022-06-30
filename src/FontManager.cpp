#include "FontManager.hpp"
#include "Game.hpp"
#include "Renderers/Ren_SDL.hpp"

#include "stb_truetype.h"
#include "sdlStbFont.h"

sdl_stb_font_cache* FontManager::LoadFont(const char* fileName, int fontSize){

    std::ifstream fontFile(fileName, std::ios::in | std::ios::binary);
    sttfont_memory font_mem;
    fontFile.seekg(0, std::ios::end);
    size_t fontFileLength = fontFile.tellg();
    fontFile.seekg(std::ios::beg);
    font_mem.alloc(fontFileLength);

    fontFile.read(font_mem.data, fontFileLength);

    sdl_stb_font_cache* font_cache = new sdl_stb_font_cache();
    font_cache->faceSize = fontSize;
    font_cache->loadFontManaged(font_mem);
    SDL_Renderer* ren = static_cast<Ren_SDL*>(Game::renderer)->Renderer();
    font_cache->bindRenderer(ren);

    fontFile.close();
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