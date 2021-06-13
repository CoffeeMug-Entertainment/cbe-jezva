#include "Components/C_SolidColour.hpp"

C_SolidColour::C_SolidColour(int r, int b, int g, int a)
{
	this->colour.r = r;
	this->colour.g = g;
	this->colour.b = b;
	this->colour.a = a;
}

C_SolidColour::~C_SolidColour(){}

void C_SolidColour::Initialize()
{
	if (owner->HasComponent<C_Transform>())
	{
		transform = owner->GetComponent<C_Transform>();
	}
	destinationRectangle.x = transform->position.x;
	destinationRectangle.y = transform->position.y;
	destinationRectangle.w = transform->width;
	destinationRectangle.h = transform->height;
}

void C_SolidColour::Update(float deltaTime)
{

	destinationRectangle.x = transform->position.x;
	destinationRectangle.y = transform->position.y;
	destinationRectangle.w = transform->width;
	destinationRectangle.h = transform->height;
}

void C_SolidColour::Render()
{
	SDL_SetRenderDrawColor(Game::renderer, this->colour.r, this->colour.g, this->colour.b, this->colour.a);
	SDL_RenderFillRect(Game::renderer, &destinationRectangle);
}