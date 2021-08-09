#ifndef C_TEXT
#define C_TEXT

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "FontManager.hpp"
#include "EntityManager.hpp"
#include "AssetManager.hpp"
#include "Game.hpp"
#include "Types/Vector2.hpp"
#include "Types/Colour.hpp"

class C_Text: public Component {
	private:
		SDL_Rect position;
		std::string text;
		std::string fontFamily;
		//SDL_Color color;
		CB::Colour colour;
		SDL_Texture* texture;
	public:
		C_Text(int x, int y, std::string text, std::string fontFamily, const CB::Colour& colour);
		C_Text(CB::Vec2 newPosition, std::string text, std::string fontFamily, const CB::Colour& colour);

		//TODO fhomolka 02/08/2021 23:30 -> Constructor that takes in transform, and a "bool follorTransform"
		//									If it should follow transform, in Update, update own position to that of the transform

		void SetLabelText(std::string text, std::string newfontFamily = "") ;

		void Render() override;
};

#endif
