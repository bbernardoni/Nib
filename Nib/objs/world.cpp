#include "world.h"
#include "../game.h"

World::World(Game& game):
	VectObj(game, game.getRes().getWorld1Model())
{
}

void World::update(){
	updateChildren();
}

void World::testCollision(VectObj& obj){
	Model* worldModel = getModel();
	Model* objModel = obj.getModel();
	const vector<Vector2i>& worldAnimNibsOff = getAnimNibsOff();
	const vector<Vector2i>& objAnimNibsOff = obj.getAnimNibsOff();
}