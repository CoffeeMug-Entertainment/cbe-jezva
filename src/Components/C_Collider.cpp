#include "Components/C_Collider.hpp"
#include "Components/C_RigidBody2D.hpp"

C_Collider::C_Collider() {}
C_Collider::~C_Collider() {}

void C_Collider::Initialize() {

	Game::entityManager->RegisterCollider(owner->GetComponent<C_RigidBody2D>()->GetBody(), this);
}

void C_Collider::OnCollisionEnter(Entity* otherEntity) {
	for(auto& func : this->onCollisionEnterFuncs)
	{
		//if(func == nullptr) continue;
		func(otherEntity);
	}
}

void C_Collider::OnCollisionExit(Entity* otherEntity) {
	for(auto& func : this->onCollisionExitFuncs)
	{
		//if(func == nullptr) continue;
		func(otherEntity);
	}
}

void C_Collider::RegisterOnEnterFunc(std::function<void(Entity*)> func)
{
	this->onCollisionEnterFuncs.emplace_back(func);
}

void C_Collider::RegisterOnExitFunc(std::function<void(Entity*)> func)
{
	this->onCollisionEnterFuncs.emplace_back(func);
}