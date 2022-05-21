#include "EntityManager.hpp"
#include "Components/C_Collider.hpp"

#include <iostream>

EntityManager::EntityManager()
{
	box2DWorld = new b2World(b2Vec2{0, 10});
}

EntityManager::~EntityManager()
{
	delete box2DWorld;
}


void EntityManager::ClearData() {
	for (auto& entity : entities) {
		entity->Destroy();
	}
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}

const int32 velIterations = 8;
const int32 posIterations = 3;
void EntityManager::Update(float deltaTime) {
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(deltaTime);
		if(!entities[i]->IsActive()){
			entities.erase(entities.begin() + i--);
		}
	}

	box2DWorld->Step(deltaTime, velIterations, posIterations);
}

void EntityManager::Render() {
	for (size_t layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
		for (auto& entity : GetEntitiesByLayer(static_cast<Layer>(layerNumber))) {
			entity->Render();
		}
	}
}

Entity& EntityManager::AddEntity(std::string entityName) {
	Entity* entity = new Entity(*this, entityName, LAYER_ONE);
	entities.emplace_back(entity);
	return *entity;
}


Entity& EntityManager::AddEntity(std::string entityName, Layer layer) {
	Entity* entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}


std::vector<Entity*> EntityManager::GetEntities() const {
	return entities;
}

Entity* EntityManager::GetEntityByName(std::string entityName) const {
    for (auto* entity: entities) {
        if (entity->name.compare(entityName) == 0) {
            return entity;
        }
    }
    return NULL;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(Layer layer) const {
	std::vector<Entity*> filteredEntities;

	for (auto& entity : entities) {
		if (entity->layer == layer) {
			filteredEntities.emplace_back(entity);
		}
	}

	return filteredEntities;
}

unsigned int EntityManager::GetEntityCount() const{
	return entities.size();
}

void EntityManager::ListAllEntities() const {
	unsigned int i = 0;
	for (auto& entity : entities) {
		//std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
		Game::logger->Log("Entity[" + std::to_string(i) + "]: " + entity->name);
		entity->ListAllComponents();
		i++;
	}
}


//Axis-Aligned Bounding Box Collision
bool AABBCollisionCheck(C_Collider* firstEntity, C_Collider* secondEntity)
{
	if (firstEntity->collider.x < secondEntity->collider.x + secondEntity->collider.w &&
		firstEntity->collider.x + firstEntity->collider.w > secondEntity->collider.x &&
		firstEntity->collider.y < secondEntity->collider.y + secondEntity->collider.h &&
		firstEntity->collider.y + firstEntity->collider.h > secondEntity->collider.y
		) {
		return true;
	}

	return false;
}

void EntityManager::CheckCollisions()
{
    for (size_t i = 0; i < entities.size() - 1; i++) {
        auto& thisEntity = entities[i];
        if (thisEntity->HasComponent<C_Collider>()) {
            C_Collider* thisCollider = thisEntity->GetComponent<C_Collider>();
            for (size_t j = i + 1; j < entities.size(); j++) {
                auto& thatEntity = entities[j];
                if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<C_Collider>()) {
                    C_Collider* thatCollider = thatEntity->GetComponent<C_Collider>();
                    if (::AABBCollisionCheck(thisCollider, thatCollider)) {
                        thisCollider->OnCollisionReported(thatCollider->owner);
                        thatCollider->OnCollisionReported(thisCollider->owner);
                    }
                }
            }
        }
    }
}
