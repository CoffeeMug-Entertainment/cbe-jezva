#include "C_BallLogic.hpp"
#include "Components/C_Collider.hpp"
#include "CB_Math.hpp"
#include <cmath>
C_BallLogic::C_BallLogic(){}

C_BallLogic::~C_BallLogic(){}

void C_BallLogic::Initialize()
{
	this->ballTransform = owner->GetComponent<C_Transform>();
	this->owner->GetComponent<C_Collider>()->RegisterFunc(FBind(&C_BallLogic::OnCollisionReported));
	//his->ballRigidBody = this->owner->GetComponent<C_RigidBody2D>();

	LaunchBall();
}

void C_BallLogic::Update(float deltaTime)
{
	if(this->ballTransform->position.y <= 1)
	{
		//ballRigidBody->velocity.y = std::abs(ballRigidBody->velocity.y);
		ballTransform->velocity.y = std::abs(ballTransform->velocity.y);
	}
	else if (this->ballTransform->position.y + this->ballTransform->height >= 599)
	{
		//ballRigidBody->velocity.y = -std::abs(ballRigidBody->velocity.y);
		ballTransform->velocity.y = -std::abs(ballTransform->velocity.y);
	}

	if (this->ballTransform->position.x <= 1)
	{
		gameManager->PointScored(1);
		ballTransform->position.x = 400;
		ballTransform->position.y = 300;
		LaunchBall();
	}
	else if(this->ballTransform->position.x + this->ballTransform->height >= 799)
	{
		gameManager->PointScored(0);
		ballTransform->position.x = 400;
		ballTransform->position.y = 300;
		LaunchBall();
	}
}

void C_BallLogic::OnCollisionReported(Entity* otherEntity) 
{

	C_Transform *otherTransform = otherEntity->GetComponent<C_Transform>();

	if (otherEntity->GetComponent<C_Collider>()->colliderTag == "Paddle")
	{
		Game::logger->Log("Collided with a paddle!");
		//ballRigidBody->velocity.x += this->accel * CB::Sign(ballRigidBody->velocity.x);
		//ballRigidBody->velocity.x = -ballRigidBody->velocity.x;

		ballTransform->velocity.x = -ballTransform->velocity.x;
		ballTransform->velocity.x += this->accel * CB::Sign(ballTransform->velocity.x);
		float verticalAngle = (ballTransform->GetCentre().y - otherTransform->GetCentre().y) / (otherTransform->height / 2);
		this->currentSpeed += this->accel;
		//ballRigidBody->velocity.y = verticalAngle * this->currentSpeed / 2;
		ballTransform->velocity.y = verticalAngle * this->currentSpeed / 2;
		return;
	}

}

void C_BallLogic::LaunchBall()
{
	int newHorDirection = Game::rng->rand_bool() ? 1 : -1; 
	//ballRigidBody->velocity = CB::Vec2{newHorDirection * this->startingSpeed, 0};
	ballTransform->velocity = CB::Vec2{newHorDirection * this->startingSpeed, 0};
}