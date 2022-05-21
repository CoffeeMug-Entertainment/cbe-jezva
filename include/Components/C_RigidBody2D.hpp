#ifndef C_RIGIDBODY2D
#define C_RIGIDBODY2D

#include "Components/C_Transform.hpp"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"

class C_RigidBody2D : public Component 
{
	public:
	enum class BodyType {STATIC = 0, DYNAMIC};
		C_RigidBody2D(BodyType type = BodyType::STATIC);
		~C_RigidBody2D();
		void Initialize() override;
		void Update([[maybe_unused]] float deltaTime) override;
		void SetVelocity(CB::Vec2 newVel);
		CB::Vec2 GetVelocity();
		void ApplyForce(CB::Vec2 force);
		void ApplyImpulse(CB::Vec2 impulse);
		void SetPosition(CB::Vec2 newPos);
		CB::Vec2 GetPosition();

		b2Body* GetBody() const;
	private:
		C_Transform *bodyTransform;
		b2BodyDef bodyDef;
		b2Body* body;
		b2PolygonShape shape;
		b2FixtureDef fixtureDef;
		BodyType type;
};

#endif