#include "Renderers/Ren_Software.hpp"
#include "Game.hpp"

Ren_Software::Ren_Software(){};
Ren_Software::~Ren_Software(){
	SDL_DestroyRenderer(renderer);
};

bool Ren_Software::Initialize(){
	Game::logger->Log("Creating an SDL_Renderer");
	this->renderer = SDL_CreateRenderer(Game::window, -1, 0);

	if (!this->renderer) {
        Game::logger->LogError("Error creating SDL_Renderer!");
		return false;
	}

	return true;
}

void Ren_Software::Render(){
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);
	
	//Call manager.render to render entities
	if (Game::entityManager->HasNoEntities()) {
		//LogError("There are no Entities in the scene!");
		return;
	}
	Game::entityManager->Render();

	SDL_RenderPresent(renderer);
}

void Ren_Software::RenderCopy(SDL_Texture* texture, SDL_Rect position){
	SDL_RenderCopy(this->renderer, texture, NULL, &position);
}

void Ren_Software::RenderCopyEx(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip){
	SDL_RenderCopyEx(this->renderer, texture, srcRect, dstRect, angle, center, flip);
}

SDL_Texture* Ren_Software::CreateTextureFromSurface(SDL_Surface *surface){
	return SDL_CreateTextureFromSurface(this->renderer, surface);
}

void Ren_Software::QueryTexture(SDL_Texture* texture, uint32_t* format, int* access, int* w, int* h){
	SDL_QueryTexture(texture, format, access, w, h);
}

void Ren_Software::SetRenderDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void Ren_Software::RenderFillRect(SDL_Rect* dstRect){
	SDL_RenderFillRect(this->renderer, dstRect);
}

void Ren_Software::FreeSurface(SDL_Surface* surface){
	SDL_FreeSurface(surface);
}