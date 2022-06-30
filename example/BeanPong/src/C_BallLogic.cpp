#include "C_BallLogic.hpp"
#include "Components/C_Collider.hpp"
#include "CB_Math.hpp"
#include <cmath>
#include "AssetManager.hpp"

C_BallLogic::C_BallLogic(){}

C_BallLogic::~C_BallLogic(){}

void C_BallLogic::Initialize()
{
	this->ballTransform = owner->GetComponent<C_Transform>();
	/*
	* Indeed, you can register methods/functions to entities Collider component
	* So, any time your Collider component is told they're colliding, it will call your methods.
	* Yes, multiple - the methods are kept in a vector
	* If you're binding methods, use the FBIND() macro
	* BEWARE: There's currently no ways to UNBIND methods/functions when bound, so generally stick binds within the entity
	*/
	this->owner->GetComponent<C_Collider>()->RegisterOnEnterFunc(FBind(&C_BallLogic::OnCollisionReported));
	this->ballRigidBody = this->owner->GetComponent<C_RigidBody2D>();

	LaunchBall();
}

void C_BallLogic::Update(float deltaTime)
{
	if(this->ballTransform->position.y <= 1)
	{
		CB::Vec2 ballVel = ballRigidBody->GetVelocity();
		ballVel.y = std::abs(ballVel.y);
		ballRigidBody->SetVelocity(ballVel);
		AudioManager::PlayWav(Game::assetManager->GetWave("bounce"));
	}
	else if (this->ballTransform->position.y + this->ballTransform->height >= 599)
	{
		CB::Vec2 ballVel = ballRigidBody->GetVelocity();
		ballVel.y = -std::abs(ballVel.y);
		ballRigidBody->SetVelocity(ballVel);
		AudioManager::PlayWav(Game::assetManager->GetWave("bounce"));
	}

	if (this->ballTransform->position.x <= 1)
	{
		gameManager->PointScored(1);
		ballRigidBody->SetPosition(CB::Vec2{400, 300});
		LaunchBall();
	}
	else if(this->ballTransform->position.x + this->ballTransform->height >= 799)
	{
		gameManager->PointScored(0);
		ballRigidBody->SetPosition(CB::Vec2{400, 300});
		LaunchBall();
	}
}

void C_BallLogic::OnCollisionReported(Entity* otherEntity) 
{
	/*
	* Here lies an ugly truth: No automatic physics handling
	* You're going to have to manage your own physics.
	* I am planning on implementing a proper physics engine, like Box2D
	* but until I do, have fun writing your own.
	*/
	C_Transform *otherTransform = otherEntity->GetComponent<C_Transform>();

	if (otherEntity->GetComponent<C_Collider>()->colliderTag == "Paddle")
	{
		CB::Vec2 ballVel = ballRigidBody->GetVelocity();
		ballVel.x = -ballVel.x;
		ballVel.x += this->accel * CB::Sign(ballVel.x);
		float verticalAngle = (ballTransform->GetCentre().y - otherTransform->GetCentre().y) / (otherTransform->height / 2);
		this->currentSpeed += this->accel;
		ballVel.y = verticalAngle * this->currentSpeed / 2;

		ballRigidBody->SetVelocity(ballVel);

		AudioManager::PlayWav(Game::assetManager->GetWave("bounce"));
		return;
	}

}

void C_BallLogic::LaunchBall()
{
	int newHorDirection = Game::rng->rand_bool() ? 1 : -1; 
	ballRigidBody->SetVelocity(CB::Vec2{newHorDirection * this->startingSpeed, 0});
}