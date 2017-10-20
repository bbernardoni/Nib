#pragma once

#include "../core/object.h"

class World: public Object {
public:
	World(Game& game);

	void update();

private:
	void draw(RenderTarget& target, RenderStates states) const;

};