#include "world.h"

World::World(Game& game):
	Object(game)
{

}

void World::update(){
	
	updateChildren();
}

void World::draw(RenderTarget& target, RenderStates states) const{
	//states.shader = &model->shader;
	Object::draw(target, states);
}