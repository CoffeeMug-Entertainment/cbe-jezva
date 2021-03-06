#ifndef GAME_HPP
#define GAME_HPP

#include "SDL.h"
//TODO: Bundle SDL with code, do not depend on users installation
//#include "SDL.h"
//#include "SDL_ttf.h"
#include <string>
#include <iostream>

#include "CoffeeBeanConfig.h"
#include "EntityManager.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "Logger.hpp"
#include "RandomNumberGenerator.hpp"
#include "Renderers/CB_Renderer.hpp"
#include "Audio/Aud_OpenAL.hpp"


class EntityManager;
class AssetManager;
class InputManager;

class Game{
    public:
        Game(std::string title);
        ~Game();
        bool IsRunning() const;
        static CB_Renderer *renderer;
        static Aud_OpenAL *audioManager;
        static SDL_Window *window;
        static SDL_Event event;
        static SDL_Rect camera;
        static AssetManager *assetManager;
        static EntityManager *entityManager;
        static InputManager *inputManager;
        static Logger *logger;
        static RandomNumberGenerator *rng;
        static CBE::CoffeeBeanConfig config;
        
        void LoadConfig(std::string filePath);
        void Run();
        void Initialize(int width = 0, int height = 0);
        void MainLoop();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

    private:
        bool isRunning;
        
		float ticksLastFrame; //number of ticks SDL reported last frame
};

#endif