#include "vectObj.h"
#include "../game.h"

VectObj::VectObj(Game& game, Model* model):
	Object(game),
	model(model)
{
	ribs.resize(model->sibs.size());
	for(size_t i=0; i<model->sibs.size(); i++){
		ribs[i] = VertexArray(LineStrip, model->sibs[i].size());
		for(size_t j=0; j<model->sibs[i].size(); j++){
			ribs[i][j].position = subToScreen(model->nibs[model->sibs[i][j]]);
		}
		addDrawable(&ribs[i]);
	}
}

void VectObj::updateChildren(){
	if(game.getFrame() % 4 == 0){
		vector<Vector2i> nibsOff;
		for(size_t i=0; i<model->nibs.size(); i++){
			nibsOff.push_back(Vector2i(getRand(), getRand()));
		}
		for(size_t i=0; i<model->sibs.size(); i++){
			for(size_t j=0; j<model->sibs[i].size(); j++){
				size_t sib = model->sibs[i][j];
				ribs[i][j].position = subToScreen(model->nibs[sib] + nibsOff[sib]);
			}
		}
	}

	model->shader.setUniform("winSize", Vector2f(game.getWinSize()));
	
	Object::updateChildren();
}

void VectObj::draw(RenderTarget& target, RenderStates states) const{
	states.shader = &model->shader;
	Object::draw(target, states);
}

int VectObj::getRand() const {
	return 0;// (rand() - RAND_MAX/2) % 300;
}

Vector2f VectObj::subToScreen(Vector2i sub) const {
	Vector2f screen;
	screen.x = sub.x / 144.0f;
	screen.y = sub.y / 144.0f;
	return screen;
}
