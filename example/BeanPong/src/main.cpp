#include <cstdlib>
#include <iostream>
#include "CoffeeBean.hpp"
#include "GameManager.hpp"


GameManager *gameManager;

int main(int argc, char *argv[])
{

	Game *game = new Game("BeanPong");

	game->Initialize(800, 600);

    gameManager = new GameManager();
    

    gameManager->MakeEntities();

    game->MainLoop();

    game->logger->Log("Freeing game");
    delete game;
	
	return 0;
}