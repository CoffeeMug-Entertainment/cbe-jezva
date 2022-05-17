#ifndef C_PLAYER_CONTROLLER
#define C_PLAYER_CONTROLLER

#include "Component.hpp"
#include "C_PaddleMover.hpp"

class C_PlayerController : public Component
{
	/* PlayerController Component
	* Not much useful here, check the cpp.
	*/
	public:
		C_PlayerController();
		~C_PlayerController();
		void Initialize() override;
		void Update(float deltaTime) override;
	private:
		C_PaddleMover *paddleMover;

};

#endif