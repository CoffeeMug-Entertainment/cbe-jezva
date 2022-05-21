#ifndef C_BALL_LOGIC
#define C_BALL_LOGIC

#include "Component.hpp"
#include "GameManager.hpp"
//#include "Components/C_Transform.hpp"
#include "Components/C_RigidBody2D.hpp"
#include "CB_Math.hpp"

class GameManager;

class C_BallLogic : public Component
{
	/*
	* BallLogic Component
	* This should've probably been couple of components, like in the case of paddles, but eh.
	*/
	public:
		C_BallLogic();
		~C_BallLogic();
		void Initialize() override;
		void Update(float deltaTime) override;
		void OnCollisionReported(Entity* otherEntity);
		void LaunchBall();
		GameManager* gameManager;
	private:
		float startingSpeed = 70;
		float currentSpeed = 70;
		float accel = 10;
		C_Transform *ballTransform;
		C_RigidBody2D *ballRigidBody;
};

#endif