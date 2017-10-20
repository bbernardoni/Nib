#pragma once

#include <SFML/Window.hpp>
#include "trigBoolInput.h"
using namespace sf;

class KeyInput: public TrigBoolInput {
public:
	KeyInput(Keyboard::Key inputKey, Trigger trig=level);

protected:
	bool getState();

private:
	Keyboard::Key key;
};
