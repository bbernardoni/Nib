#pragma once

#include "../core/object.h"
#include "../core/machine.h"
#include "../res.h"
#include <vector>

class Player: public Object {
public:
	Player(Game& game);

	void update();

private:
	void draw(RenderTarget& target, RenderStates states) const;
	int getRand();
	Vector2f subToScreen(Vector2i sub);

	void noJump();
	void holdJump();
	void realseJump();

	float vertColl(float vel);

	vector<VertexArray> ribs;
	PlayerModel* model;

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
