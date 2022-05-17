#include "C_PaddleMover.hpp"
#include <string>

C_PaddleMover::C_PaddleMover(){}

C_PaddleMover::~C_PaddleMover(){}

void C_PaddleMover::Initialize() {

	this->paddleTransform = owner->GetComponent<C_Transform>();

}

void C_PaddleMover::Update(float deltaTime) {

	float movementDistance = this->movementDir * this->paddleSpeed * deltaTime;

	// Very primitive way of clamping paddles to the screen
	if (paddleTransform->position.y + movementDistance <= -1 ||
		paddleTransform->position.y + paddleTransform->height + movementDistance >= 601
		) {
		movementDistance = 0;
	}

	paddleTransform->Translate(CB::Vec2{0, movementDistance});
	
}

void C_PaddleMover::SetMoveDir(int dir) {
	this->movementDir = std::clamp<int>(dir, -1, 1);
}