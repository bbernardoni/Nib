#include "world.h"
#include "../game.h"

World::World(Game& game):
	VectObj(game, game.getRes().getWorld1Model())
{
}

void World::update(){
	updateChildren();
}