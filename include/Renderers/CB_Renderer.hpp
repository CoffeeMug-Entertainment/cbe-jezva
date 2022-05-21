#ifndef CB_RENDERER
#define CB_RENDERER

#include "CB_SDL.h"
#include "Types/Colour.hpp"

class CB_Renderer
{
public:
	CB_Renderer(){};
	virtual ~CB_Renderer() {};
	
	virtual bool Initialize(){return false;};
	virtual void Render(){};

	virtual void RenderCopy(SDL_Texture* texture, SDL_Rect position) = 0;
	virtual void RenderCopyEx(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip) = 0;
	virtual SDL_Texture* CreateTextureFromSurface(SDL_Surface *surface) = 0;
	virtual void QueryTexture(SDL_Texture* texture, uint32_t* format, int* access, int* w, int* h) = 0;

	virtual void SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
	virtual void SetRenderDrawColor(CB::RGBA& newColour) = 0;
	virtual void RenderFillRect(SDL_Rect* destinationRectangle) = 0;

	virtual void FreeSurface(SDL_Surface* surface) = 0;

	void SetClearColour(CB::Colour newColour){this->clearColour = newColour;};
protected:
	CB::Colour clearColour;
};

#endif