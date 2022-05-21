#include "Components/C_SolidColour.hpp"

C_SolidColour::C_SolidColour(int r, int b, int g, int a)
{
	this->colour.FromRGBA8(r, g, b, a);
}

C_SolidColour::C_SolidColour(CB::Colour newColour)
{
	this->colour = newColour;
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

void C_SolidColour::Update([[maybe_unused]] float deltaTime)
{

	destinationRectangle.x = transform->position.x;
	destinationRectangle.y = transform->position.y;
	destinationRectangle.w = transform->width;
	destinationRectangle.h = transform->height;
}

void C_SolidColour::Render()
{
	Game::renderer->SetRenderDrawColor(this->colour.red * 255, this->colour.green * 255, this->colour.blue * 255, this->colour.alpha * 255);
	Game::renderer->RenderFillRect(&destinationRectangle);
}