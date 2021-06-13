#include "InputManager.hpp"


InputManager::InputManager(){}

InputManager::~InputManager(){}

void InputManager::ProcessInput()
{
	std::string eventKeyCode;

	// depending on the type of event, go through the map, find the key, update it's status
	switch(Game::event.type)
	{
		case SDL_KEYDOWN:
			eventKeyCode = std::to_string(Game::event.key.keysym.sym);
			for(auto& registeredKey : this->registeredKeys)
			{
				if (eventKeyCode.compare(registeredKey.second.SDLKeyStringCode) == 0)
				{
					registeredKey.second.IsPressed = true;
					break;
				}
			}
			break;
		case SDL_KEYUP:
			eventKeyCode = std::to_string(Game::event.key.keysym.sym);
			for(auto& registeredKey : this->registeredKeys)
			{
				if (eventKeyCode.compare(registeredKey.second.SDLKeyStringCode) == 0)
				{
					registeredKey.second.IsPressed = false;
					break;
				}
			}
			break;
		default:
			break;
	}
}

void InputManager::RegisterKey(std::string inputId, std::string keyString)
{
	registeredKeys.insert({inputId, {GetSDLKeyStringCode(keyString), false}});
}

bool InputManager::IsKeyDown(std::string inputId)
{
	// is this ID even registered?
	auto iter = this->registeredKeys.find(inputId);
	if (iter == this->registeredKeys.end())
	{
		Game::logger->Log("[InputManager | IsKeyDown] " + inputId + " is not a registered key!");
		return false;
	}


	return this->registeredKeys[inputId].IsPressed;
}