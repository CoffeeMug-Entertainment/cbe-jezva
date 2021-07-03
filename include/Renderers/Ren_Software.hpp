#ifndef CB_REN_SOFTWARE
#define CB_REN_SOFTWARE

#include "CB_Renderer.hpp"
#include <SDL2/SDL.h>

class Ren_Software : public CB_Renderer
{
public:
	Ren_Software();
	~Ren_Software();

	bool Initialize() override;
	void Render() override;

	void RenderCopy(SDL_Texture* texture, SDL_Rect position) override;
	void RenderCopyEx(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip) override;
	SDL_Texture* CreateTextureFromSurface(SDL_Surface *surface) override;
	void QueryTexture(SDL_Texture* texture, uint32_t* format, int* access, int* w, int* h) override;

	void SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
	void RenderFillRect(SDL_Rect* dstRect) override;
	void FreeSurface(SDL_Surface* surface) override;
private:
	SDL_Renderer *renderer;

};

#endif