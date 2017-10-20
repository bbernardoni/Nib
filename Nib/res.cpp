#include "res.h"

Res::Res(){
	playerMod = nullptr;
	monoFont = nullptr;
}

PlayerModel* Res::getPlayerModel(){
	if(!playerMod)
		playerMod = new PlayerModel("res/player.mod");
	return playerMod;
}

Font* Res::getMonoFont(){
	if(!monoFont){
		monoFont = new Font();
		monoFont->loadFromFile("res/DejaVuSansMono.ttf");
	}
	return monoFont;
}
