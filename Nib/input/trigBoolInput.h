#pragma once

#include "input.h"

enum Trigger{level, rise, fall};

class TrigBoolInput: public BoolInput {
public:
	TrigBoolInput(Trigger trigger);

	void update();

protected:
	virtual bool getState() = 0;

private:
	Trigger trig;
	bool last;
};
