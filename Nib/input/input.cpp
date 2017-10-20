#include "input.h"

std::vector<InputBase*> InputBase::vec;

InputBase::InputBase(){
	vec.push_back(this);
}

InputBase::~InputBase(){
	vec.erase(remove(vec.begin(), vec.end(), this), vec.end());
}

void InputBase::updateAll(){
	for(auto input: vec){
		input->update();
	}
}
