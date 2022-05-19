#include <cstdlib>
#include <iostream>
#include "CoffeeBean.hpp"
#include "GameManager.hpp"

/*
* BeanPong - main
* Simple example project on how to use CoffeeBean
* For the sake of shortness, I'm not following all the 'good practices'
* The bad practices should be apparent.
*/

int main(int argc, char *argv[]) {
	Game game = Game("BeanPong");
	game.Initialize(800, 600);
    // Not required, but I like having some sort of manager, to handle my 'level construction' logic, track states, etc.
    GameManager gameManager = GameManager();
    gameManager.MakeEntities();
    game.MainLoop();
    game.logger->Log("Freeing game");
	
	return 0;
}