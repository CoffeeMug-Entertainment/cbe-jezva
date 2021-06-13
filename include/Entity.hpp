#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Constants.h"
#include "EntityManager.hpp"
#include "Component.hpp"

#include <vector>
#include <map>
#include <string>

class EntityManager;
class Component;

class Entity {
    public:
        std::string name;
        Layer layer;

        Entity();
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        Entity(EntityManager& manager, std::string name, Layer layer);
        virtual ~Entity();
        std::vector<Component*> GetComponents();
        virtual void Update(float deltaTime);
        virtual void Render();
        void Destroy();
        bool IsActive() const;
        void ListAllComponents() const;

        template<typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args){
			T* newComponent(new T(std::forward<TArgs>(args)...));

			newComponent->owner = this;
			components.emplace_back(newComponent);
			componentTypeMap[&typeid(*newComponent)] = newComponent;
			newComponent->Initialize();
			return *newComponent;
		}

        template<typename T>
		T* GetComponent(){
			return static_cast<T*>(componentTypeMap[&typeid(T)]);
		}

		template<typename T>
		bool HasComponent() const{
			return componentTypeMap.count(&typeid(T));
		}

    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;
};

#endif