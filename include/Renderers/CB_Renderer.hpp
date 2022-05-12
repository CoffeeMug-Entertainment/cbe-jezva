#ifndef CB_RENDERER
#define CB_RENDERER

#include <SDL2/SDL.h>
#include "Types/Colour.hpp"

class CB_Renderer
{
public:
	CB_Renderer(){};
	~CB_Renderer(){};
	
	virtual bool Initialize(){return false;};
	virtual void Render(){};

	virtual void RenderCopy(SDL_Texture* texture, SDL_Rect position){};
	virtual void RenderCopyEx(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip){};
	virtual SDL_Texture* CreateTextureFromSurface(SDL_Surface *surface){ return nullptr;};
	virtual void QueryTexture(SDL_Texture* texture, uint32_t* format, int* access, int* w, int* h){};

	virtual void SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a){};
	virtual void RenderFillRect(SDL_Rect* destinationRectangle){};

	virtual void FreeSurface(SDL_Surface* surface){};

	void SetClearColour(CB::Colour newColour){this->clearColour = newColour;};
protected:
	CB::Colour clearColour;
};

#endif