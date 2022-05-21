#include "EntityManager.hpp"
#include "Components/C_Collider.hpp"
#include "Components/C_RigidBody2D.hpp"
#include "box2d/b2_contact.h"

#include <iostream>

EntityManager::EntityManager()
{
	contactListener = BasicListener();
	box2DWorld = new b2World(b2Vec2{0, 10});
	box2DWorld->SetContactListener(&contactListener);
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

void EntityManager::RegisterCollider(b2Body* body, C_Collider* collider) {
	contactListener.RegisterCollider(body, collider);
}

BasicListener::BasicListener(){}
BasicListener::~BasicListener(){}

void BasicListener::BeginContact(b2Contact* contact) {
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	if (bodyMap.contains(bodyA)) {
		b2BodyUserData& bodyBUserData = bodyB->GetUserData();
		C_RigidBody2D* rBody = (C_RigidBody2D*)bodyBUserData.pointer;
		bodyMap[bodyA]->OnCollisionEnter(rBody->owner);
	}

	if (bodyMap.contains(bodyB)) {
		b2BodyUserData& bodyBUserData = bodyA->GetUserData();
		C_RigidBody2D* rBody = (C_RigidBody2D*)bodyBUserData.pointer;
		bodyMap[bodyB]->OnCollisionEnter(rBody->owner);
	}
}
void BasicListener::EndContact(b2Contact* contact) {
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	if (bodyMap.contains(bodyA)) {
		b2BodyUserData& bodyBUserData = bodyB->GetUserData();
		C_RigidBody2D* rBody = (C_RigidBody2D*)bodyBUserData.pointer;
		bodyMap[bodyA]->OnCollisionExit(rBody->owner);
	}

	if (bodyMap.contains(bodyB)) {
		b2BodyUserData& bodyBUserData = bodyA->GetUserData();
		C_RigidBody2D* rBody = (C_RigidBody2D*)bodyBUserData.pointer;
		bodyMap[bodyB]->OnCollisionExit(rBody->owner);
	}
}

void BasicListener::RegisterCollider(b2Body* body, C_Collider* collider) {
	bodyMap.emplace(body, collider);
}