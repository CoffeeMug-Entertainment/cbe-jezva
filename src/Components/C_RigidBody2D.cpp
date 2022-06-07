#include "Components/C_RigidBody2D.hpp"
#include "Components/C_Collider.hpp"
#include "Game.hpp"
#include "Constants.h"

C_RigidBody2D::C_RigidBody2D(BodyType type) {
	this->type = type;
}

C_RigidBody2D::~C_RigidBody2D(){
	Game::entityManager->box2DWorld->DestroyBody(this->body);
}

void C_RigidBody2D::Initialize() {
	this->bodyTransform = this->owner->GetComponent<C_Transform>();
	switch (this->type)
	{
		case BodyType::STATIC:
			this->bodyDef.type = b2_staticBody;
			break;	
		case BodyType::DYNAMIC:
			this->bodyDef.type = b2_dynamicBody;
			break;	
		default:
			this->bodyDef.type = b2_staticBody;
			break;
	}
	this->bodyDef.position.Set(bodyTransform->GetCentre().x / PIXELS_PER_METER, bodyTransform->GetCentre().y / PIXELS_PER_METER);
	this->bodyDef.fixedRotation = true;
	b2BodyUserData uData;
	uData.pointer = (uintptr_t)this;
	this->bodyDef.userData = uData;
	this->body = Game::entityManager->box2DWorld->CreateBody(&bodyDef);
	this->shape.SetAsBox((bodyTransform->width * bodyTransform->scale / PIXELS_PER_METER) / 2, (bodyTransform->height * bodyTransform->scale / PIXELS_PER_METER) / 2);
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
}

void C_RigidBody2D::Update([[maybe_unused]] float deltaTime) {
	b2Vec2 newPos = this->body->GetPosition();
	bodyTransform->position.x = (newPos.x * PIXELS_PER_METER) - (bodyTransform->width / 2);
	bodyTransform->position.y = (newPos.y * PIXELS_PER_METER) - (bodyTransform->height / 2);
}

void C_RigidBody2D::SetPosition(CB::Vec2 newPos) {
	this->bodyTransform->position.x = newPos.x;
	this->bodyTransform->position.y = newPos.y;
	this->body->SetTransform(b2Vec2{bodyTransform->GetCentre().x / PIXELS_PER_METER, 
							bodyTransform->GetCentre().y / PIXELS_PER_METER}, 0);
}

CB::Vec2 C_RigidBody2D::GetPosition() {
	b2Vec2 newPos = this->body->GetPosition();
	return CB::Vec2{(newPos.x * PIXELS_PER_METER) - (bodyTransform->width / 2),
					(newPos.y * PIXELS_PER_METER) - (bodyTransform->height / 2)
	};
}

void C_RigidBody2D::SetVelocity(CB::Vec2 newVel) {
	this->body->SetLinearVelocity(b2Vec2{newVel.x, newVel.y});
}

CB::Vec2 C_RigidBody2D::GetVelocity() {
	b2Vec2 vel = body->GetLinearVelocity();
	return CB::Vec2{vel.x, vel.y};
}

void C_RigidBody2D::ApplyForce(CB::Vec2 force) {
	this->body->ApplyForceToCenter(b2Vec2{force.x, force.y}, true);
}

void C_RigidBody2D::ApplyImpulse(CB::Vec2 impulse) {
	this->body->ApplyLinearImpulseToCenter(b2Vec2{impulse.x, impulse.y}, true);
}

b2Body* C_RigidBody2D::GetBody() const {
	return this->body;
}