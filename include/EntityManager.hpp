#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Game.hpp"
#include "Entity.hpp"
#include "Component.hpp"
//#include "C_Collider.hpp" //Do not include, avoid circular inclusion
#include "Constants.h"
#include "box2d/b2_world.h"

#include <vector>
#include <string>
#include <type_traits>

class Entity;
//class C_Collider;

class EntityManager{
	public:
		b2World* box2DWorld;
        EntityManager();
        ~EntityManager();
		void ClearData();
		void Update(float deltaTime);
		void Render();
		bool HasNoEntities();
		Entity& AddEntity(std::string entityName);
		Entity& AddEntity(std::string entityName, Layer layer);
		std::vector<Entity*> GetEntities() const;
		std::vector<Entity*> GetEntitiesByLayer(Layer layer) const;
		Entity* GetEntityByName(std::string entityName) const;
		unsigned int GetEntityCount() const;
		void ListAllEntities() const;
		std::string CheckEntityCollisions(Entity& entity) const;
		void CheckCollisions();
		void DestroyInactiveEntities();

	private:
		std::vector<Entity*> entities;
		//bool AABBCollisionCheck(C_Collider* firstEntity, C_Collider* secondEntity);
};

#endif
