#include "player.h"
#include "../game.h"

Player::Player(Game& game):
	Object(game),
	model(game.getRes().getPlayerModel()),
	jumpFSM(this)
{
	ribs.resize(model->sibs.size());
	for(size_t i=0; i<model->sibs.size(); i++){
		ribs[i] = VertexArray(LineStrip, model->sibs[i].size());
		for(size_t j=0; j<model->sibs[i].size(); j++){
			ribs[i][j].position = subToScreen(model->nibs[model->sibs[i][j]]);
		}
		addDrawable(&ribs[i]);
	}

	moveMaxSpeed = 10.0f;
	moveAccel = 4.0f;
	moveDrag = 0.7f;
	jumpSpeed = 20.0f;
	jumpDrag = 0.97f;
	gravity = -2.0f;

	moveVel = 0.0f;
	jumpFSM.setState(&Player::noJump);
	vertVel = 0.0f;
}

void Player::update(){
	Dir dir = game.getInput().getPDir();

	moveVel *= moveDrag;
	moveVel += moveAccel*DirHelper::getHori(dir);
	if(moveVel > moveMaxSpeed) moveVel = moveMaxSpeed;
	else if(moveVel < -moveMaxSpeed) moveVel = -moveMaxSpeed;
	move(moveVel, 0.0f);

	jumpFSM.updateState();

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
	
	updateChildren();
}

void Player::draw(RenderTarget& target, RenderStates states) const{
	states.shader = &model->shader;
	Object::draw(target, states);
}

int Player::getRand(){
	return 0;// (rand() - RAND_MAX/2) % 300;
}

Vector2f Player::subToScreen(Vector2i sub){
	Vector2f screen;
	screen.x = sub.x / 144.0f;
	screen.y = sub.y / 144.0f;
	return screen;
}

void Player::noJump(){
	Vector2f pos = getPosition();
	bool onGround = pos.y >= 800;
	bool jump = game.getInput().getPJump();

	vertVel += gravity;
	if(jump && onGround){
		jumpFrame = game.getFrame();
		vertVel = jumpSpeed;
		jumpFSM.setState(&Player::holdJump);
	}

	vertVel = vertColl(vertVel);
	move(0.0f, -vertVel);
}

void Player::holdJump(){
	bool jump = game.getInput().getPJump();

	vertVel *= jumpDrag;
	if(!jump)
		jumpFSM.setState(&Player::noJump);
	else if(game.getFrame()-jumpFrame > 15)
		jumpFSM.setState(&Player::realseJump);

	vertVel = vertColl(vertVel);
	move(0.0f, -vertVel);
}

void Player::realseJump(){
	bool jump = game.getInput().getPJump();

	vertVel += gravity;
	if(!jump)
		jumpFSM.setState(&Player::noJump);

	vertVel = vertColl(vertVel);
	move(0.0f, -vertVel);
}

float Player::vertColl(float vel){
	Vector2f pos = getPosition();

	if(pos.y - vel > 800)
		return pos.y - 800;

	return vel;
}