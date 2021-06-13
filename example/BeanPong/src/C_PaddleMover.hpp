#ifndef C_PADDLEMOVER
#define C_PADDLEMOVER

#include "Component.hpp"
#include "Components/C_Transform.hpp"

class C_PaddleMover : public Component
{
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