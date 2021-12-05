#include "Renderers/Ren_SDL.hpp"
#include "Game.hpp"

Ren_SDL::Ren_SDL(){};
Ren_SDL::~Ren_SDL(){
	SDL_DestroyRenderer(renderer);
};

bool Ren_SDL::Initialize(){
	Game::logger->Log("Creating an SDL_Renderer");
	this->renderer = SDL_CreateRenderer(Game::window, -1, 0);

	if (!this->renderer) {
        Game::logger->LogError("Error creating SDL_Renderer!");
		return false;
	}

	return true;
}

void Ren_SDL::Render(){
	SDL_Color clearColor = this->clearColour.ToSDLColor();
	SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b, 255);
	SDL_RenderClear(renderer);
	
	//Call manager.render to render entities
	if (Game::entityManager->HasNoEntities()) {
		//LogError("There are no Entities in the scene!");
		return;
	}
	Game::entityManager->Render();

	SDL_RenderPresent(renderer);
}

void Ren_SDL::RenderCopy(SDL_Texture* texture, SDL_Rect position){
	SDL_RenderCopy(this->renderer, texture, NULL, &position);
}

void Ren_SDL::RenderCopyEx(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip){
	SDL_RenderCopyEx(this->renderer, texture, srcRect, dstRect, angle, center, flip);
}

SDL_Texture* Ren_SDL::CreateTextureFromSurface(SDL_Surface *surface){
	return SDL_CreateTextureFromSurface(this->renderer, surface);
}

void Ren_SDL::QueryTexture(SDL_Texture* texture, uint32_t* format, int* access, int* w, int* h){
	SDL_QueryTexture(texture, format, access, w, h);
}

void Ren_SDL::SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void Ren_SDL::RenderFillRect(SDL_Rect* dstRect){
	SDL_RenderFillRect(this->renderer, dstRect);
}

void Ren_SDL::FreeSurface(SDL_Surface* surface){
	SDL_FreeSurface(surface);
}