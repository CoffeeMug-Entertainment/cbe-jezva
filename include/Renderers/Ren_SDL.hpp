#ifndef CB_Ren_SDL
#define CB_Ren_SDL

#include "CB_Renderer.hpp"
#include "CB_SDL.h"

class Ren_SDL : public CB_Renderer
{
public:
	Ren_SDL();
	~Ren_SDL();

	bool Initialize() override;
	void Render() override;

	void RenderCopy(SDL_Texture* texture, SDL_Rect position) override;
	void RenderCopyEx(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip) override;
	SDL_Texture* CreateTextureFromSurface(SDL_Surface *surface) override;
	void QueryTexture(SDL_Texture* texture, uint32_t* format, int* access, int* w, int* h) override;

	void SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
	void SetRenderDrawColor(CB::RGBA& newColour) override;
	void RenderFillRect(SDL_Rect* dstRect) override;
	void FreeSurface(SDL_Surface* surface) override;

	SDL_Renderer* Renderer() const;
private:
	SDL_Renderer *renderer;

};

#endif