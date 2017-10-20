#pragma once

#include "input/input.h"
#include "input/boolDirInput.h"

class GameInput {
public:
	GameInput();
	~GameInput();

	Dir getPDir();
	bool getPJump();

private:
	DirInput* pDir;
	BoolInput* pJump;
};