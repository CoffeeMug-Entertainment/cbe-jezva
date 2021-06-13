#ifndef C_TEXT
#define C_TEXT

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "FontManager.hpp"
#include "EntityManager.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Types/Vector2.hpp"

class C_Text: public Component {
	private:
		SDL_Rect position;
		std::string text;
		std::string fontFamily;
		SDL_Color color;
		SDL_Texture* texture;
	public:
		C_Text(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color);
		C_Text(CB::Vec2 newPosition, std::string text, std::string fontFamily, const SDL_Color& color);

		void SetLabelText(std::string text, std::string newfontFamily = "") ;

		void Render() override;
};

#endif
