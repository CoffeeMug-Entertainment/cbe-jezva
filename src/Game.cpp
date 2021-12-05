#include "Game.hpp"
#include "EntityManager.hpp"
#include "Renderers/Ren_SDL.hpp"


//SDL_Renderer* Game::renderer;
CB_Renderer* Game::renderer;
SDL_Window* Game::window;
AssetManager* Game::assetManager;
EntityManager* Game::entityManager;
InputManager* Game::inputManager;
SDL_Event Game::event;
Logger* Game::logger;
RandomNumberGenerator* Game::rng;
CoffeeBeanConfig Game::config;
        

Game::Game(std::string title) 
{
	this->isRunning = false;
    this->config.title = title;

    entityManager = new EntityManager();
    assetManager = new AssetManager(entityManager);
    inputManager = new InputManager();
    logger = new Logger();
    rng = new RandomNumberGenerator();
    
}

Game::~Game()
{
	logger->Log("Freeing assetManager");
	delete assetManager;
	logger->Log("Freeing entityManager");
	delete entityManager;
	logger->Log("Freeing inputManager");
	delete inputManager;
	logger->Log("Freeing rng");
	delete rng;
	logger->Log("Freeing logger, good bye <3");
	delete logger;
}

bool Game::IsRunning() const {
	return this->isRunning;
}

void Game::LoadConfig(std::string filePath){
    //TODO fhomolka 17/10/2020 20:37 -> Load from .cfg file
}

void Game::Run(){
    Initialize(800, 600);
    //MainLoop();
}

void Game::Initialize(int width, int height){
	logger->Log("Initializing SDL!");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger->LogError("Error Initializing SDL");
		return;
	}

	logger->Log("Initializing SDL_TTF");
	if(TTF_Init() != 0){
        logger->LogError("Error Initializing SDL_TTF");
		return;
	}

	logger->Log("Creating an SDL Window!");
	window = SDL_CreateWindow(
			this->config.title.c_str(), 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			width, 
			height, 
			SDL_WINDOW_BORDERLESS
	);

	if (!window) {
        logger->LogError("Error Creating SDL window!");
		return;
	}

	this->renderer = new Ren_SDL();

	if(!this->renderer->Initialize()){
		return;
	}

	this->renderer->SetClearColour(CB::Colour{0.08f, 0.08f, 0.08f, 1.0f});

	isRunning = true;
	//return;

}

void Game::MainLoop(){
    while (this->isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
    
    Destroy();
}

void Game::LoadLevel(/*std::string levelName*/){


}

void Game::ProcessInput(){
	SDL_PollEvent(&event);

	//Quit on quit event and Escape-key press
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN: // move this somewhere else, my dude
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			break;
		default:
			break;
	}

	//have input manager process inputs as well
	inputManager->ProcessInput();
}

void Game::Update(){

	// Wait until enough ms elapsed since the last frame
	unsigned int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}

	//Delta time is the difference in ticks from last frame - converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000;

	// Clamp deltaTime to a max value
	deltaTime = (deltaTime > 1.0f) ? 1 : deltaTime;

	// Sets the num of tick since init, to be used in the next cycle
	ticksLastFrame = SDL_GetTicks();

	//call manager.update to update entities
	entityManager->Update(deltaTime);
}

void Game::Render(){

	this->renderer->Render();
}

void Game::Destroy(){
    logger->Log("Destroying renderer");
	delete renderer;
    logger->Log("Destroying window");
	SDL_DestroyWindow(window);
    logger->Log("Qutting SDL");
	SDL_Quit();
}
