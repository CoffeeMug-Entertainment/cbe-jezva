#include "Components/C_Text.hpp"

C_Text::C_Text(int x, int y, std::string text, std::string fontFamily, const CB::Colour& colour) {
	this->position.x = x;
	this->position.y = y;
	this->text = text;
	this->fontFamily = fontFamily;
	this->colour = colour;
	SetLabelText(text, fontFamily);
}

C_Text::C_Text(CB::Vec2 newPosition, std::string text, std::string fontFamily, const CB::Colour& colour) {

	this->position.x = newPosition.x;
	this->position.y = newPosition.y;
	this->text = text;
	this->fontFamily = fontFamily;
	this->colour = colour;
	SetLabelText(text, fontFamily);
}

void C_Text::SetLabelText(std::string text, std::string newfontFamily) {

	if (newfontFamily != "")
	{
		this->fontFamily = newfontFamily;
	}

	auto testFont = Game::assetManager->GetFont(fontFamily);
	SDL_Surface* surface = TTF_RenderText_Blended(testFont, text.c_str(), this->colour.ToSDLColor());
	texture = Game::renderer->CreateTextureFromSurface(surface);
	Game::renderer->FreeSurface(surface);
	Game::renderer->QueryTexture(texture, NULL, NULL, &position.w, &position.h);
}

void C_Text::Render() {
	FontManager::Draw(texture, position);
}
