#include "gameInput.h"

GameInput::GameInput(){
	pDir = new BoolDirInput(Keyboard::W, Keyboard::D, Keyboard::S, Keyboard::A);
	pJump = new KeyInput(Keyboard::Space);
}

GameInput::~GameInput(){
	delete pDir;
}

Dir GameInput::getPDir(){
	return pDir->get();
}

bool GameInput::getPJump(){
	return pJump->get();
}