#ifndef C_TILE
#define C_TILE

#include <SDL2/SDL.h>
#include "../EntityManager.hpp"
#include "../AssetManager.hpp"
#include "Types/Vector2.hpp"
//#include "Data/Tilemap.hpp"

class C_Tile: public Component {
	public:
		SDL_Texture *texture;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
		CB::Vec2 position;
		int margin;
		int tileSize;
		int scale;

		//Constructors from texture
		C_Tile(std::string assetTextureId, int sourceCoordX = 0, int sourceCoordY = 0, int tileSize = 16, int margin = 0, int x = 0, int y = 0, int tileScale = 1);
		C_Tile(std::string assetTextureId, int sourceCoordX = 0, int sourceCoordY = 0, int tileSize = 16, int margin = 0, CB::Vec2 position = {0, 0}, int tileScale = 1);
		C_Tile(std::string assetTextureId, CB::Vec2 sourceCoords = {0, 0}, int tileSize = 16, int margin = 0, CB::Vec2 position = {0, 0}, int tileScale = 1);

		/*
		//Constructors from tilemap
		C_Tile(std::string tilemapId, int sourceRectX = 0, int sourceRectY = 0, int x = 0, int y = 0, tileScale = 1);
		C_Tile(std::string tilemapId, int sourceRectX = 0, int sourceRectY = 0, CB::Vec2 = {0, 0} tileScale = 1);
		C_Tile(std::string tilemapId, CB::Vec2 sourceCoords = {0, 0} CB::Vec2 position = {0, 0} tileScale = 1);
		*/

		~C_Tile();

		void Update(float deltaTime) override;

		void Render() override;
};

#endif
