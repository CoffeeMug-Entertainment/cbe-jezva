#include "Components/C_Transform.hpp"

C_Transform::C_Transform(int posX, int posY, int w, int h, float s) 
{
	this->position = CB::Vec2{static_cast<float>(posX), static_cast<float>(posY)};
	this->width = w;
	this->height = h;
	this->scale = s;
}

C_Transform::C_Transform(CB::Vec2 newPos, int w, int h, float s) 
{
	this->position = newPos;
	this->width = w;
	this->height = h;
	this->scale = s;
}

void C_Transform::Initialize() {}

void C_Transform::Update(float deltaTime) 
{
	
}


CB::Vec2 C_Transform::GetCentre()
{
	return CB::Vec2{this->position.x + this->width / 2, this->position.y + this->height / 2};
}

void C_Transform::Translate(CB::Vec2 translationValue)
{
	this->position += translationValue;
}