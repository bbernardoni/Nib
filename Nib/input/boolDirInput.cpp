#include "boolDirInput.h"

BoolDirInput::BoolDirInput(BoolInput* northIn, BoolInput* eastIn, BoolInput* southIn, BoolInput* westIn):
	north(northIn),
	east(eastIn),
	south(southIn),
	west(westIn) {}

BoolDirInput::BoolDirInput(Keyboard::Key northKey, Keyboard::Key eastKey, Keyboard::Key southKey, Keyboard::Key westKey, Trigger trig):
	north(new KeyInput(northKey, trig)),
	east(new KeyInput(eastKey, trig)),
	south(new KeyInput(southKey, trig)),
	west(new KeyInput(westKey, trig)) {}


BoolDirInput::~BoolDirInput(){
	delete north;
	delete east;
	delete south;
	delete west;
}

void BoolDirInput::update(){
	int hori = east->get() - west->get();
	int vert = north->get() - south->get();
	val = DirHelper::getDir(hori, vert);
}
