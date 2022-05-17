#ifndef C_PADDLE_AI
#define C_PADDLE_AI

#include "Component.hpp"
#include "Components/C_Transform.hpp"
#include "C_PaddleMover.hpp"

class C_PaddleAI : public Component
{
	/* PaddleAI Component
	* A pretty dumb ai, that just tracks the ball's center, and then tries to move towards it
	*/
	public:
		C_PaddleAI();
		~C_PaddleAI();

		void Initialize() override;
		void Update(float deltaTime) override;

	private:
		C_Transform *paddleTransform;
		C_Transform *ballTransform;
		C_PaddleMover *paddleMover;
};

#endif