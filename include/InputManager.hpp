#ifndef COFFEEBEAN_INPUT
#define COFFEEBEAN_INPUT

#include "Game.hpp"
#include <unordered_map>

struct KeyInfo
{
	std::string SDLKeyStringCode;
	bool IsPressed;
};

class InputManager
{
public:

	InputManager();
	~InputManager();
	void ProcessInput();
	void RegisterKey(std::string inputId, std::string keyString);
	bool IsKeyDown(std::string inputId);

private:

	std::unordered_map<std::string, KeyInfo> registeredKeys;

	std::string GetSDLKeyStringCode(std::string key) 
	{
		if (key.compare("up") == 0) return "1073741906";
		if (key.compare("down") == 0) return "1073741905";
		if (key.compare("left") == 0) return "1073741904";
		if (key.compare("right") == 0) return "1073741903";
		if (key.compare("space") == 0) return "32"; 
		return std::to_string(static_cast<int>(key[0]));
	}
	
};

#endif