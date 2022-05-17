#ifndef C_PADDLEMOVER
#define C_PADDLEMOVER

#include "Component.hpp"
#include "Components/C_Transform.hpp"

class C_PaddleMover : public Component
{

	/*
	* PaddleMover Component
	* Doesn't do much on it's own
	* It expects a direction - set with SetMoveDir(),
	* and then it translates the paddle, by the owner's C_Transform
	*/

	public:
		C_PaddleMover();
		~C_PaddleMover();
		void Initialize() override;
		void Update(float deltaTime) override;
		void SetMoveDir(int dir);
	private:
		C_Transform *paddleTransform;
		float paddleSpeed = 80;
		int movementDir = 0;
	
};

#endif