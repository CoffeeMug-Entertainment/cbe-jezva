#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Entity.hpp"

class Entity;

class Component{
	public:
		Entity* owner;
		Component(){};
		virtual ~Component(){};
		virtual void Initialize(){};
		virtual void Update(float deltaTime){};
		virtual void Render(){};
};

#endif