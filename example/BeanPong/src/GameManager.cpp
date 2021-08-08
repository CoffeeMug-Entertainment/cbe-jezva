#include "GameManager.hpp"
#include "Components/C_Transform.hpp"
#include "Components/C_RigidBody2D.hpp"
#include "Components/C_SolidColour.hpp"
#include "Components/C_Collider.hpp"
#include "Components/C_Text.hpp"
#include "C_BallLogic.hpp"
#include "C_PaddleMover.hpp"
#include "C_PaddleAI.hpp"
#include "C_PlayerController.hpp"
#include "Types/Colour.hpp"

GameManager::GameManager(){}

GameManager::~GameManager(){}

void GameManager::MakeEntities()
{
	//TODO fhomolka 06/06/2021 15:31 -> Move this
	Game::assetManager->LoadFromAssetsJson("./assets/assets.json");
	

	//Ball
	Entity& ball = Game::entityManager->AddEntity("Ball");
	ball.AddComponent<C_Transform>(390, 290, 10, 10, 1);
	C_Transform* ballTransform = ball.GetComponent<C_Transform>();
	ball.AddComponent<C_SolidColour>(CB::Colour{0.58f, 0.0f, 0.58f, 1.0f});
	ball.AddComponent<C_Collider>("ball", ballTransform->position.x, ballTransform->position.y, ballTransform->width, ballTransform->height);
	C_BallLogic& ballLogic = ball.AddComponent<C_BallLogic>();
	ballLogic.gameManager = this;

	//Paddles
	Entity& playerPaddle = Game::entityManager->AddEntity("PlayerPaddle");
	C_Transform& playerTransform = playerPaddle.AddComponent<C_Transform>(10, 250, 10, 100, 1);
	playerPaddle.AddComponent<C_SolidColour>(CB::Colour{0.0f, 0.58f, 0.58f, 1.0f});
	playerPaddle.AddComponent<C_Collider>("Paddle", playerTransform.position.x, playerTransform.position.y, playerTransform.width, playerTransform.height);
	playerPaddle.AddComponent<C_PaddleMover>();
	playerPaddle.AddComponent<C_PlayerController>();

	Entity& rightPaddle = Game::entityManager->AddEntity("RightPaddle");
	C_Transform& rightPaddleTransform = rightPaddle.AddComponent<C_Transform>(800 - 10 - 10, 350, 10, 100, 1);
	rightPaddle.AddComponent<C_SolidColour>(CB::Colour{0.58f, 0.58f, 0.0f, 1.0f});
	rightPaddle.AddComponent<C_Collider>("Paddle", rightPaddleTransform.position.x, rightPaddleTransform.position.y, rightPaddleTransform.width, rightPaddleTransform.height);
	rightPaddle.AddComponent<C_PaddleMover>();
	rightPaddle.AddComponent<C_PaddleAI>();


	//UI
	Entity& playerScore = Game::entityManager->AddEntity("PlayerScore");
	playerScore.AddComponent<C_Text>(300, 20, "0", "silkBold", SDL_Color{255, 255, 255, 255});
	playerScoreLabel = playerScore.GetComponent<C_Text>(); //fhomolka 06/06/2021 20:19 -> Tried getting it directly from AddComponent, demon possession happened

	Entity& AIScore = Game::entityManager->AddEntity("AIScore");
	AIScore.AddComponent<C_Text>(450, 20, "0", "silkBold", SDL_Color{255, 255, 255, 255});
	aiScoreLabel = AIScore.GetComponent<C_Text>();


}

void GameManager::SetGame()
{
	
}

void GameManager::PointScored(int playerId)
{

	switch(playerId)
	{
		case 0:
			Game::logger->Log("Player Scored!");
			this->playerScore += 1;
			this->playerScoreLabel->SetLabelText(std::to_string(playerScore));
			break;
		case 1:
			Game::logger->Log("AI Scored!");
			this->aiScore += 1;
			this->aiScoreLabel->SetLabelText(std::to_string(aiScore));
			break;
		default:
			Game::logger->Log("The heck?");
			break;
	}
	
}