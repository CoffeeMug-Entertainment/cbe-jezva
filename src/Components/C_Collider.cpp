#include "Components/C_Collider.hpp"


C_Collider::C_Collider(std::string colliderTag, int x, int y, int width, int height) {
	this->colliderTag = colliderTag;
	//this->collider = {x, y, width, height};
	
	this->collider.x = x;
	this->collider.y = y;
	this->collider.w = width;
	this->collider.h = height;
}


void C_Collider::Initialize(){
	if (owner->HasComponent<C_Transform>()) {
		transform = owner->GetComponent<C_Transform>();
		//sourceRectangle = {0, 0, transform->width, transform->height};
		//destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
	}
}

void C_Collider::Update(float deltaTime){
	collider.x = static_cast<int>(transform->position.x); 
	collider.y = static_cast<int>(transform->position.y);
	collider.w = transform->width * transform->scale;
	collider.h = transform->height * transform->scale;
}

void C_Collider::OnCollisionReported(Entity* otherEntity)
{
	//owner->OnCollisionReported(otherEntity);
	for(auto& func : this->onCollisionFuncs)
	{
		//if(func == nullptr) continue;
		func(otherEntity);
	}
}

/*void C_Collider::RegisterFunc(void (*newFunc)(Entity*))
{
	this->onCollisionFuncs.emplace_back(newFunc);
	Game::logger->Log("Registered a func");
}*/

void C_Collider::RegisterFunc(std::function<void(Entity*)> func)
{
	this->onCollisionFuncs.emplace_back(func);
}