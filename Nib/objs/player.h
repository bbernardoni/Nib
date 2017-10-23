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

	int moveMaxSpeed;
	int moveAccel;
	float moveDrag;
	int jumpSpeed;
	float jumpDrag;
	int gravity;

	Machine jumpFSM;
	int jumpFrame;
};
