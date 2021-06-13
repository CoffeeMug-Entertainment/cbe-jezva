#ifndef CB_C_TRANSFORM
#define CB_C_TRANSFORM

#include <SDL2/SDL.h>
#include "../Component.hpp"
#include "Types/Vector2.hpp"
//#include "Game.hpp"

class C_Transform: public Component {
	public:
		CB::Vec2 position = {0, 0};
		int width;
		int height;
		int scale;
		
		C_Transform(int posX, int posY, int w, int h, int s = 1);

		C_Transform(CB::Vec2 newPos, int w, int h, int s = 1);

		void Initialize() override;

		void Update(float deltaTime) override;

		CB::Vec2 GetCentre();

		void Translate(CB::Vec2 translationValue);

		//HACK fhomolka 06/06/2021 19:14 -> No, I do not like this being here, but RigidBody2D is currently broken
		void AddVelocity(CB::Vec2 newVelocity);
		CB::Vec2 velocity = {0, 0};
		int deceleration;
};

#endif
