#pragma once

#include <SFML/Graphics.hpp>
#include "models/model.h"
using namespace sf;

class Res {
public:
	Res();

	Model* getPlayerModel();
	Model* getWorld1Model();
	Font* getMonoFont();

private:
	Model* playerMod;
	Model* world1Model;
	Font* monoFont;
};
