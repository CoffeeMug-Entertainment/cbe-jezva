#ifndef CB_TILEMAP
#define CB_TILEMAP

#include "CB_SDL.h"
#include <Types/Vector2.hpp>
#include <string>

namespace CB
{
	struct Tilemap
	{
		std::string Id;
		SDL_Texture* texture;
		int tileSize;
		int margin;

		Tilemap(std::string tilemapId, SDL_Texture* texture, int tileSize, int margin = 0)
		{
			this->Id = tilemapId;
			this->texture = texture;
			this->tileSize = tileSize;
			this->margin = margin;
		}

		SDL_Rect GetTileRect(CB::Vec2 tileCoord)
		{
			//TODO(fhomolka): margins
			SDL_Rect srcRect = SDL_Rect
			{
				static_cast<int>(tileCoord.x) * tileSize,
				static_cast<int>(tileCoord.y) * tileSize,
				tileSize,
				tileSize
			};
			return srcRect;
		}
	};

	// We should allow both
	using Spritesheet = Tilemap;
}

#endif