#include "Components/C_RigidBody2D.hpp"
#include "Components/C_Collider.hpp"

//NOTE fhomolka: DO NOT USE! Check Header!

C_RigidBody2D::C_RigidBody2D(CB::Vec2 velocity, float deceleration) {
	this->velocity = velocity;
	this->deceleration = deceleration;
}

C_RigidBody2D::~C_RigidBody2D(){}

void C_RigidBody2D::Initialize() {
	this->bodyTransform = this->owner->GetComponent<C_Transform>();
}

void C_RigidBody2D::Update(float deltaTime) {
	//TODO fhomolka 06/06/2021 17:23 -> Make nicer
	
	bodyTransform->Translate(velocity * deltaTime);

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

void C_RigidBody2D::AddVelocity(CB::Vec2 newVelocity) {
	this->velocity += newVelocity;
}
