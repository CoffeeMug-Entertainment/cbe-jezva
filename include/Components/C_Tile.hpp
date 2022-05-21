#ifndef C_TILE
#define C_TILE

#include "Data/Tilemap.hpp"
#include "Components/C_Transform.hpp"

class C_Tile: public Component {
	public:
		C_Tile(std::string tilemapId, CB::Vec2 tileCoords = {0, 0}, int scale = 1);
		~C_Tile();

		void Update([[maybe_unused]] float deltaTime) override;
		void Initialize() override;
		void Render() override;
	private: 
		C_Transform* transform;
		CB::Tilemap* tilemap;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
		CB::Vec2 coords;
		int scale;
};

#endif
