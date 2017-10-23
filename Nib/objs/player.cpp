#include "player.h"
#include "../game.h"

Player::Player(Game& game):
	VectObj(game, game.getRes().getPlayerModel()),
	jumpFSM(this)
{
	pos = Vector2i(-100800, -36000);

	moveMaxSpeed = 1440;
	moveAccel = 576;
	moveDrag = 0.7f;

	jumpSpeed = -2880;
	jumpDrag = 0.95f;
	gravity = 288;

	jumpFSM.setState(&Player::noJump);
}

void Player::update(){
	Dir dir = game.getInput().getPDir();

	vel.x = int(vel.x*moveDrag);
	vel.x += moveAccel*DirHelper::getHori(dir);
	if(vel.x > moveMaxSpeed) vel.x = moveMaxSpeed;
	else if(vel.x < -moveMaxSpeed) vel.x = -moveMaxSpeed;

	jumpFSM.updateState();
	if(pos.y + vel.y > 53000)
		vel.y = 53000 - pos.y;

	updateChildren();
}

void Player::noJump(){
	bool onGround = pos.y >= 50400;
	bool jump = game.getInput().getPJump();

	vel.y += gravity;
	if(jump && onGround){
		jumpFrame = game.getFrame();
		vel.y = jumpSpeed;
		jumpFSM.setState(&Player::holdJump);
	}
}

void Player::holdJump(){
	bool jump = game.getInput().getPJump();

	vel.y = int(vel.y*jumpDrag);
	if(!jump)
		jumpFSM.setState(&Player::noJump);
	else if(game.getFrame()-jumpFrame > 15)
		jumpFSM.setState(&Player::realseJump);
}

void Player::realseJump(){
	bool jump = game.getInput().getPJump();

	vel.y += gravity;
	if(!jump)
		jumpFSM.setState(&Player::noJump);
}
