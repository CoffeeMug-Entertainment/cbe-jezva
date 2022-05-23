#ifndef C_SOLID_COLOUR
#define C_SOLID_COLOUR

#include "SDL.h"
#include "../Component.hpp"
#include "C_Transform.hpp"
#include "Types/Colour.hpp"

class C_SolidColour: public Component {
public:
	//SDL_Color colour;
	CB::Colour colour;
	SDL_Rect destinationRectangle;
	C_Transform* transform;


	C_SolidColour(int r=255, int b=255, int g=255, int a=255);
	C_SolidColour(CB::Colour newColour);
	~C_SolidColour();

	void Initialize() override;
	void Update([[maybe_unused]] float deltaTime) override;
	void Render() override;
};

#endif