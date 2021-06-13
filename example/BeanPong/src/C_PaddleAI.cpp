#include "C_PaddleAI.hpp"
#include "Game.hpp"
#include <algorithm>
#include <string>
#include "CB_Math.hpp"
#include <typeinfo>

C_PaddleAI::C_PaddleAI(){}

C_PaddleAI::~C_PaddleAI(){}

void C_PaddleAI::Initialize()
{
	this->paddleTransform = owner->GetComponent<C_Transform>();
	Entity *ballEntity = Game::entityManager->GetEntityByName("Ball");
	this->ballTransform = ballEntity->GetComponent<C_Transform>();
	this->paddleMover = this->owner->GetComponent<C_PaddleMover>();
}

void C_PaddleAI::Update(float deltaTime)
{
	int dir = CB::Sign(ballTransform->GetCentre().y - paddleTransform->GetCentre().y);
	paddleMover->SetMoveDir(dir);
}