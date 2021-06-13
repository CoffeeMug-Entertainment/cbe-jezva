#include "Components/C_Text.hpp"

C_Text::C_Text(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color) {
	this->position.x = x;
	this->position.y = y;
	this->text = text;
	this->fontFamily = fontFamily;
	this->color = color;
	SetLabelText(text, fontFamily);
}

C_Text::C_Text(CB::Vec2 newPosition, std::string text, std::string fontFamily, const SDL_Color& color) {

	this->position.x = newPosition.x;
	this->position.y = newPosition.x;
	this->text = text;
	this->fontFamily = fontFamily;
	this->color = color;
	SetLabelText(text, fontFamily);
}

void C_Text::SetLabelText(std::string text, std::string newfontFamily) {

	if (newfontFamily != "")
	{
		this->fontFamily = newfontFamily;
	}

	auto testFont = Game::assetManager->GetFont(fontFamily);
	SDL_Surface* surface = TTF_RenderText_Blended(testFont, text.c_str(), this->color);
	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
}

void C_Text::Render() {
	FontManager::Draw(texture, position);
}