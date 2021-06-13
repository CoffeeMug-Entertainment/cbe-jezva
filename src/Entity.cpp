#include "Entity.hpp"
#include "Game.hpp"

Entity::Entity(): manager(*Game::entityManager){
    this->manager = *Game::entityManager;
    this->name = "Unnamed Entity";
    this->isActive = true;
}

Entity::Entity(EntityManager& manager): manager(manager){
    this->name = "Unnamed Entity";
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name): manager(manager){
    this->name = name;
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, Layer layer): manager(manager){
    this->name = name;
    this->layer = layer;
    this->isActive = true;
}

Entity::~Entity(){}

std::vector<Component*> Entity::GetComponents(){
	return components;
}

void Entity::Update(float deltaTime){

	for (auto& component: components) {
		component->Update(deltaTime);
	}
}

void Entity::Render(){

	for(auto& component: components){
		component->Render();
	}
}

void Entity::Destroy() {

	this->isActive = false;
}

bool Entity::IsActive() const{

	return this->isActive;
}

void Entity::ListAllComponents() const {
    for (auto mapElement: componentTypeMap) {
        Game::logger->Log("    Component<" + std::string(mapElement.first->name()) + ">");
    }
}

