#include "player.h"
#include "../game.h"

Player::Player(Game& game):
	VectObj(game, game.getRes().getPlayerModel()),
	jumpFSM(this)
{
	moveMaxSpeed = 10.0f;
	moveAccel = 4.0f;
	moveDrag = 0.7f;
	jumpSpeed = 20.0f;
	jumpDrag = 0.95f;
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

	updateChildren();
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