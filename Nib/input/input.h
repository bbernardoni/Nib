#pragma once

#include <vector>
#include <algorithm>
#include "dirHelper.h"

class InputBase {
public:
	InputBase();
	virtual ~InputBase();
	virtual void update() = 0;

	static void updateAll();
private:
	static std::vector<InputBase*> vec;
};

template <class T>
class Input: public InputBase {
public:
	Input(): val(){}
	virtual ~Input(){}
	T get(){ return val; }

protected:
	T val;
};

typedef Input<bool> BoolInput;
typedef Input<float> FloatInput;
typedef Input<Dir> DirInput;
typedef Input<char> CharInput;
