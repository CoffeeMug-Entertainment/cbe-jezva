#ifndef C_PADDLE_AI
#define C_PADDLE_AI

#include "Component.hpp"
#include "Components/C_Transform.hpp"
#include "C_PaddleMover.hpp"

class C_PaddleAI : public Component
{
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