#pragma once

#include "input.h"
#include "dirHelper.h"

class FloatDirInput: public DirInput {
public:
	FloatDirInput(FloatInput* horiIn, FloatInput* vertIn);
	~FloatDirInput();

	void update();

private:
	FloatInput* hori;
	FloatInput* vert;
};
