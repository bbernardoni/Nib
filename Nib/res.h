#pragma once

#include <SFML/Graphics.hpp>
#include "models/playerModel.h"
using namespace sf;

class Res {
public:
	Res();

	PlayerModel* getPlayerModel();
	Font* getMonoFont();

private:
	PlayerModel* playerMod;
	Font* monoFont;
};
