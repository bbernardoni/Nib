#pragma once

#include "input.h"
#include "dirHelper.h"
#include "keyInput.h"

class BoolDirInput: public DirInput {
public:
	BoolDirInput(BoolInput* northIn, BoolInput* eastIn, BoolInput* southIn, BoolInput* westIn);
	BoolDirInput(Keyboard::Key northKey, Keyboard::Key eastKey, Keyboard::Key southKey, Keyboard::Key westKey, Trigger trig=level);
	~BoolDirInput();

	void update();

private:
	BoolInput* north;
	BoolInput* east;
	BoolInput* south;
	BoolInput* west;
};
