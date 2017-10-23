#include "vectObj.h"
#include "../game.h"

VectObj::VectObj(Game& game, const Model& model):
	Object(game),
	model(model)
{
	pos = Vector2i(0, 0);
	vel = Vector2i(0, 0);

	animNibsOff.resize(model.nibs.size());
	fuzzNibsOff.resize(model.nibs.size());
	for(size_t i=0; i<model.nibs.size(); i++){
		animNibsOff[i] = Vector2i(0, 0);
		fuzzNibsOff[i] = Vector2i(0, 0);
	}

	ribs.resize(model.sibs.size());
	for(size_t i=0; i<model.sibs.size(); i++){
		ribs[i] = VertexArray(LineStrip, model.sibs[i].size());
		addDrawable(&ribs[i]);
	}
}

void VectObj::preDraw(){
	if(game.getFrame() % 4 == 0){
		//fuzzNibs();
	}
	calcRibs();

	pos += vel;
	setPosition(Vector2f(game.getWinSize()/2u) + subToScreen(pos));

	model.shader.setUniform("winSize", Vector2f(game.getWinSize()));
}

const Model& VectObj::getModel(){
	return model;
}

const vector<Vector2i>& VectObj::getAnimNibsOff(){
	return animNibsOff;
}

void VectObj::draw(RenderTarget& target, RenderStates states) const{
	states.shader = &model.shader;
	Object::draw(target, states);
}

Vector2f VectObj::subToScreen(Vector2i sub) const {
	Vector2f screen;
	screen.x = sub.x / 144.0f;
	screen.y = sub.y / 144.0f;
	return screen;
}

void VectObj::fuzzNibs(){
	for(size_t i=0; i<fuzzNibsOff.size(); i++){
		fuzzNibsOff[i].x = (rand() - RAND_MAX/2) % 300;
		fuzzNibsOff[i].y = (rand() - RAND_MAX/2) % 300;
	}
}

void VectObj::calcRibs(){
	for(size_t i=0; i<model.sibs.size(); i++){
		for(size_t j=0; j<model.sibs[i].size(); j++){
			size_t sib = model.sibs[i][j];
			Vector2i nib = model.nibs[sib] + animNibsOff[sib] + fuzzNibsOff[sib];
			ribs[i][j].position = subToScreen(nib);
		}
	}
}
