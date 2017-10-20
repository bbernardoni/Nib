#include "keyInput.h"

KeyInput::KeyInput(Keyboard::Key inputKey, Trigger trig):
	TrigBoolInput(trig),
	key(inputKey) {}

bool KeyInput::getState(){
	return Keyboard::isKeyPressed(key);
}
