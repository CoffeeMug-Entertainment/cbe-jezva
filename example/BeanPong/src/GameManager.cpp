#include "GameManager.hpp"
#include "Components/C_Transform.hpp"
#include "Components/C_RigidBody2D.hpp"
#include "Components/C_SolidColour.hpp"
#include "Components/C_Collider.hpp"
#include "Components/C_RigidBody2D.hpp"
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
	Game::entityManager->box2DWorld->SetGravity(b2Vec2{0, 0});
	/*
	* Loading from JSON works.
	* It's not required, and you can make your own loader
	* and pass the data over to AssetManager methods
	* (Obviously, check AssetManager.hpp to see what's available)
	*/
	//TODO fhomolka 06/06/2021 15:31 -> Move this
	Game::assetManager->LoadFromAssetsJson("./assets/assets.json");
	
	/*
	* Entities don't get a Transform Component when they're created, like with some engines
	* Remember to add it if you want to use engine-defined components, since most of them require it
	*/

	//Ball
	Entity& ball = Game::entityManager->AddEntity("Ball");
	ball.AddComponent<C_Transform>(390, 290, 10, 10, 1);
	C_Transform* ballTransform = ball.GetComponent<C_Transform>();
	ball.AddComponent<C_SolidColour>(CB::Colour{0.58f, 0.0f, 0.58f, 1.0f});
	ball.AddComponent<C_RigidBody2D>(C_RigidBody2D::BodyType::DYNAMIC);
	ball.AddComponent<C_Collider>("Ball");
	C_BallLogic& ballLogic = ball.AddComponent<C_BallLogic>();
	ballLogic.gameManager = this;

	//Paddles
	int paddleWidth = 10;
	int paddleHeight = 100;
	int paddleStartingPosY = 250;

	Entity& playerPaddle = Game::entityManager->AddEntity("PlayerPaddle");
	C_Transform& playerTransform = playerPaddle.AddComponent<C_Transform>(10, paddleStartingPosY, paddleWidth, paddleHeight);
	playerPaddle.AddComponent<C_SolidColour>(CB::Colour{0.0f, 0.58f, 0.58f, 1.0f});
	playerPaddle.AddComponent<C_RigidBody2D>(C_RigidBody2D::BodyType::DYNAMIC);
	playerPaddle.AddComponent<C_Collider>("Paddle");
	playerPaddle.AddComponent<C_PaddleMover>();
	playerPaddle.AddComponent<C_PlayerController>();

	Entity& rightPaddle = Game::entityManager->AddEntity("RightPaddle");
	C_Transform& rightPaddleTransform = rightPaddle.AddComponent<C_Transform>(800 - 10 - paddleWidth, paddleStartingPosY, paddleWidth, paddleHeight);
	rightPaddle.AddComponent<C_SolidColour>(CB::Colour{0.58f, 0.58f, 0.0f, 1.0f});
	rightPaddle.AddComponent<C_RigidBody2D>(C_RigidBody2D::BodyType::DYNAMIC);
	rightPaddle.AddComponent<C_Collider>("Paddle");
	rightPaddle.AddComponent<C_PaddleMover>();
	rightPaddle.AddComponent<C_PaddleAI>();


	//UI
	Entity& playerScore = Game::entityManager->AddEntity("PlayerScore");
	playerScore.AddComponent<C_Text>(300, 20, "0", "silkBold", CB::Colour{1.0f, 1.0f, 1.0f, 1.0f});
	playerScoreLabel = playerScore.GetComponent<C_Text>(); //fhomolka 06/06/2021 20:19 -> Tried getting it directly from AddComponent, demon possession happened

	Entity& AIScore = Game::entityManager->AddEntity("AIScore");
	AIScore.AddComponent<C_Text>(450, 20, "0", "silkBold", CB::Colour{1.0f, 1.0f, 1.0f, 1.0f});
	aiScoreLabel = AIScore.GetComponent<C_Text>();

	/*
	* The engine does music
	* Only 1 song at a time.
	* Volume value optional (0.0f - 1.0f), if omitted, it will be played at max volume
	* For SFX check C_BallLogic::Update or GameManager::Pointscored
	*/
	AudioManager::PlayWav(Game::assetManager->GetWave("relax"));
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
			AudioManager::PlayWav(Game::assetManager->GetWave("player_score"));
			break;
		case 1:
			Game::logger->Log("AI Scored!");
			this->aiScore += 1;
			this->aiScoreLabel->SetLabelText(std::to_string(aiScore));
			AudioManager::PlayWav(Game::assetManager->GetWave("ai_score"));
			break;
		default: //Here to silence warnings and check if it's snowing in hell
			Game::logger->Log("The heck?");
			break;
	}
}