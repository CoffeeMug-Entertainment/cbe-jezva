#ifndef C_RIGIDBODY2D
#define C_RIGIDBODY2D

// TODO: fhomolka 06/06/21 18:59
/*
* This garbage is god damn broken
* When all of this velocity nonsense was in C_Transform, it worked fine
* but now it just doesn't work.
* WHY?
*/


#include "Component.hpp"
#include "Components/C_Transform.hpp"
#include "Types/Vector2.hpp"

class C_RigidBody2D : public Component 
{
	public:
		C_RigidBody2D(CB::Vec2 velocity = {0, 0}, float deceleration = 0);
		~C_RigidBody2D();
		void Initialize() override;
		void Update(float deltaTime) override;
		void AddVelocity(CB::Vec2 newVelocity);
		CB::Vec2 velocity;
		float deceleration;

	private:
		C_Transform *bodyTransform;
};

#endif