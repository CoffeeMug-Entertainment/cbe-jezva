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

	this->position = newPosition;
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
	this->text = text;

	this->font_cache = Game::assetManager->GetFont(fontFamily);
}

void C_Text::Render() {
	FontManager::Draw(this->font_cache, this->position, this->text);
}
