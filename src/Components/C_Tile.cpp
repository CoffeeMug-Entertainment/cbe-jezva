#include "Components/C_Tile.hpp"
#include "Game.hpp"

C_Tile::C_Tile(std::string assetTextureId, int sourceCoordX, int sourceCoordY, int tileSize, int margin, int x, int y, int tileScale) 
{
	texture = Game::assetManager->GetTexture(assetTextureId);

	sourceRectangle.x = sourceCoordX * tileSize;
	sourceRectangle.y = sourceCoordY * tileSize;
	sourceRectangle.w = tileSize;
	sourceRectangle.h = tileSize;

	if (sourceRectangle.x > tileSize)
	{
		sourceRectangle.x += margin;
	}

	if (sourceRectangle.y > tileSize)
	{
		sourceRectangle.y += margin;
	}

	destinationRectangle.x = x;
	destinationRectangle.y = y;
	destinationRectangle.w = tileSize * tileScale;
	destinationRectangle.h = tileSize * tileScale;

	position.x = x;
	position.y = y;
}

C_Tile::C_Tile(std::string assetTextureId, int sourceCoordX, int sourceCoordY, int tileSize, int margin, CB::Vec2 position, int tileScale)
{
	texture = Game::assetManager->GetTexture(assetTextureId);

	sourceRectangle.x = sourceCoordX * tileSize;
	sourceRectangle.y = sourceCoordY * tileSize;
	sourceRectangle.w = tileSize;
	sourceRectangle.h = tileSize;

	if (sourceRectangle.x > tileSize)
	{
		sourceRectangle.x += margin;
	}

	if (sourceRectangle.y > tileSize)
	{
		sourceRectangle.y += margin;
	}

	destinationRectangle.x = position.x;
	destinationRectangle.y = position.y;
	destinationRectangle.w = tileSize * tileScale;
	destinationRectangle.h = tileSize * tileScale;

	this->position = position;

}

C_Tile::C_Tile(std::string assetTextureId, CB::Vec2 sourceCoords, int tileSize, int margin, CB::Vec2 position, int tileScale)
{
	texture = Game::assetManager->GetTexture(assetTextureId);

	sourceRectangle.x = sourceCoords.x * tileSize;
	sourceRectangle.y = sourceCoords.y * tileSize;
	sourceRectangle.w = tileSize;
	sourceRectangle.h = tileSize;

	if (sourceRectangle.x > tileSize)
	{
		sourceRectangle.x += margin;
	}

	if (sourceRectangle.y > tileSize)
	{
		sourceRectangle.y += margin;
	}

	destinationRectangle.x = position.x;
	destinationRectangle.y = position.y;
	destinationRectangle.w = tileSize * tileScale;
	destinationRectangle.h = tileSize * tileScale;

	this->position = position;
}


C_Tile::~C_Tile() 
{
    SDL_DestroyTexture(texture);
}

void C_Tile::Update(float deltaTime)
{
    destinationRectangle.x = position.x; //- Game::camera.x;
    destinationRectangle.y = position.y; //- Game::camera.y;
}

void C_Tile::Render() 
{
    TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
}