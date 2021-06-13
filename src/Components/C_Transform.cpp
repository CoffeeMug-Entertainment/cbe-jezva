#include "Components/C_Transform.hpp"

C_Transform::C_Transform(int posX, int posY, int w, int h, int s) 
{
	this->position = CB::Vec2(posX, posY);
	this->width = w;
	this->height = h;
	this->scale = s;

	this->velocity = CB::Vec2(0, 0);
	this->deceleration = 0;
}

C_Transform::C_Transform(CB::Vec2 newPos, int w, int h, int s) 
{
	this->position = newPos;
	this->width = w;
	this->height = h;
	this->scale = s;

	this->velocity = CB::Vec2(0, 0);
	this->deceleration = 0;
}

void C_Transform::Initialize() {}

void C_Transform::Update(float deltaTime) 
{
	Translate(velocity * deltaTime);

	if (deceleration == 0)
	{
		return;
	}

	if (velocity.x > 0)
	{
		velocity.x -= deceleration;
	}
	else if (velocity.x < 0)
	{
		velocity.x += deceleration;
	}

	if (velocity.y > 0)
	{
		velocity.y -= deceleration;
	}
	else if (velocity.y < 0)
	{
		velocity.y += deceleration;
	}
}


CB::Vec2 C_Transform::GetCentre()
{
	return CB::Vec2(this->position.x + this->width / 2, this->position.y + this->height / 2);
}

void C_Transform::AddVelocity(CB::Vec2 newVelocity) {
	this->velocity += newVelocity;
}

void C_Transform::Translate(CB::Vec2 translationValue)
{
	this->position += translationValue;
}