#include "Components/C_Tile.hpp"
#include "Game.hpp"

C_Tile::C_Tile(std::string tilemapId, CB::Vec2 tileCoords, int scale)
{
	this->tilemap = Game::assetManager->GetTilemap(tilemapId);
	this->coords = tileCoords;
	this->scale = scale;
}

C_Tile::~C_Tile() 
{
}

void C_Tile::Initialize()
{
	transform = owner->GetComponent<C_Transform>();
	this->sourceRectangle = this->tilemap->GetTileRect(coords);
}

void C_Tile::Update(float deltaTime)
{
	(void)deltaTime;
    destinationRectangle.x = static_cast<int>(transform->position.x) - Game::camera.x;
	destinationRectangle.y = static_cast<int>(transform->position.y) - Game::camera.y;
	destinationRectangle.w = transform->width * transform->scale;
	destinationRectangle.h = transform->height * transform->scale;
}

void C_Tile::Render() 
{
    TextureManager::Draw(this->tilemap->texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
}