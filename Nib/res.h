#pragma once

#include <SFML/Graphics.hpp>
#include "models/model.h"
using namespace sf;

class Res {
public:
	Res();

	const Model& getPlayerModel();
	const Model& getWorld1Model();
	const Font& getMonoFont();

private:
	Model* playerMod;
	Model* world1Model;
	Font* monoFont;
};
