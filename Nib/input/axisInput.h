#pragma once

#include <SFML/Window.hpp>
#include "input.h"
using namespace sf;

class AxisInput: public FloatInput {
public:
	AxisInput();

	void update();

private:

};
