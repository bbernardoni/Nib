#include "game.h"

int main(int argc, const char* argv[]){
	Game game;
	while(game.isRunning()) game.update();
	return 0;
}
