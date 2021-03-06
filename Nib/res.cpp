#include "res.h"

Res::Res(){
	playerMod = nullptr;
	monoFont = nullptr;
}

const Model& Res::getPlayerModel(){
	if(!playerMod)
		playerMod = new Model("res/player.mod");
	return *playerMod;
}

const Model& Res::getWorld1Model(){
	if(!world1Model)
		world1Model = new Model("res/world1.mod");
	return *world1Model;
}

const Font& Res::getMonoFont(){
	if(!monoFont){
		monoFont = new Font();
		monoFont->loadFromFile("res/DejaVuSansMono.ttf");
	}
	return *monoFont;
}
