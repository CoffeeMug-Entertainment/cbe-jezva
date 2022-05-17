#ifndef BEANPONG_GAMEMANAGER
#define BEANPONG_GAMEMANAGER

#include "CoffeeBean.hpp"
#include "Components/C_Text.hpp"

class Ball;

class GameManager
{
	/*
	* GameManager class
	* Honestly, you're better off reading GameManager.cpp
	*/
	public:
		GameManager();
		~GameManager();
		void MakeEntities();
		void SetGame();
		void PointScored(int playerId);
	private:

		int playerScore = 0;
		int aiScore = 0;

		C_Text *playerScoreLabel;
		C_Text *aiScoreLabel;

		//Entity* ball;
		//Entity* playerPaddle;
};

#endif