#pragma once

#include <queue>
#include "input.h"
using namespace std;

class TextInput: public CharInput {
public:
	void update();
	static void reset();
	static void set(char c);

private:
	static char text;
};
