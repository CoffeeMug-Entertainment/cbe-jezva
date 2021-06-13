#ifndef CB_TILEMAP
#define CB_TILEMAP

#include "AssetManager.hpp"
#include "Game.hpp"
#include <Types/Vector2.hpp>
#include <string>

namespace CB
{
	struct Tilemap
	{
		std::string Id;
		SDL_Texture* tilemapTexture;
		int tileSize;
		int margin;

		Tilemap(std::string tilemapId, std::string textureId, int tileSize, int margin = 0)
		{
			this->Id = tilemapId;
			this->tilemapTexture = Game::assetManager->GetTexture(textureId);
			this->tileSize = tileSize;

		}

		CB::Vec2 GetTile(int x, int y);
	}
}



#endif