#pragma once

#include <SFML/Graphics.hpp>
#include "core/object.h"
#include "objs/player.h"
#include "input/textInput.h"
#include "gameInput.h"
using namespace sf;

/*
TODO
Add world building

*/

class Game: public Object {
public:
	Game();
	~Game();

	void update();

	bool isRunning();
	Vector2u getWinSize();

	Res& getRes();
	GameInput& getInput();
	int getFrame();

private:
	RenderWindow win;

	Res res;
	GameInput gIn;
	int frame;

	Player player;
	RectangleShape ground;
};
