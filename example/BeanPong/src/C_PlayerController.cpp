#include "C_PlayerController.hpp"

std::string paddleUpKeyCode = "paddleUp";
std::string paddleDownKeyCode = "paddleDown";

C_PlayerController::C_PlayerController(){}

C_PlayerController::~C_PlayerController(){}

void C_PlayerController::Initialize() {
	paddleMover = owner->GetComponent<C_PaddleMover>();
	/*
	* Registering the key into the input manager let's us check whether a key is pressed by checking the ID we registered
	* InputManager does not memorise who gave it the ID, so you could check whether a button is pressed from another class
	* (IF you're sure that key exists, that is)
	*/
	Game::inputManager->RegisterKey(paddleUpKeyCode, "w");
	Game::inputManager->RegisterKey(paddleDownKeyCode, "s");
}

void C_PlayerController::Update(float deltaTime)
{
	if (Game::inputManager->IsKeyDown(paddleUpKeyCode))
	{
		paddleMover->SetMoveDir(-1);
	}
	else if(Game::inputManager->IsKeyDown(paddleDownKeyCode))
	{
		paddleMover->SetMoveDir(1);
	}
	else //HACK: Sometimes the paddle slides down - investigate
	{
		paddleMover->SetMoveDir(0);
	}
}