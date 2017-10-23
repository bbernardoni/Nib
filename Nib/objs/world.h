#pragma once

#include "../core/vectObj.h"
#include "../res.h"

class World: public VectObj {
public:
	World(Game& game);

	void update();

	void testCollision(VectObj& obj);
private:

};
