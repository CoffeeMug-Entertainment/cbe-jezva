#ifndef CB_C_TRANSFORM
#define CB_C_TRANSFORM

#include "CB_SDL.h"
#include "../Component.hpp"
#include "Types/Vector2.hpp"
//#include "Game.hpp"

class C_Transform: public Component {
	public:
		CB::Vec2 position = {0, 0};
		int width;
		int height;
		float scale;
		
		C_Transform(int posX, int posY, int w, int h, float s = 1.0f);

		C_Transform(CB::Vec2 newPos, int w, int h, float s = 1.0f);

		void Initialize() override;

		void Update(float deltaTime) override;

		CB::Vec2 GetCentre();

		void Translate(CB::Vec2 translationValue);
};

#endif
