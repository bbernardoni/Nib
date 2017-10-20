#include "floatDirInput.h"

FloatDirInput::FloatDirInput(FloatInput* horiIn, FloatInput* vertIn):
	hori(horiIn),
	vert(vertIn) {}

FloatDirInput::~FloatDirInput(){
	delete hori;
	delete vert;
}

void FloatDirInput::update(){
	int horiVal = (hori->get() > 0.0f) - (hori->get() < 0.0f);
	int vertVal = (vert->get() > 0.0f) - (vert->get() < 0.0f);
	val = DirHelper::getDir(horiVal, vertVal);
}
