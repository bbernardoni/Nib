#pragma once

#include "../core/vectObj.h"
#include "../core/machine.h"
#include "../res.h"

class Player: public VectObj {
public:
	Player(Game& game);

	void update();

private:
	void noJump();
	void holdJump();
	void realseJump();

	float vertColl(float vel);

	float moveMaxSpeed;
	float moveAccel;
	float moveDrag;
	float jumpSpeed;
	float jumpDrag;
	float gravity;

	float moveVel;
	Machine jumpFSM;
	float vertVel;
	int jumpFrame;
};
