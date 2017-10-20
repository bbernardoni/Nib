#include "dirHelper.h"

namespace DirHelper{
	Dir getDir(int hori, int vert){
		return Dir(vert*3 + hori + 4);
	}

	int getHori(Dir dir){
		return dir%3 - 1;
	}
	int getVert(Dir dir){
		return dir/3 - 1;
	}
	
	Dir flip(Dir dir){
		return Dir(8-dir);
	}
	Dir rotateCW(Dir dir){
		return Dir((dir*7+6)%10);
	}
	Dir rotateCCW(Dir dir){
		return Dir((dir*3+2)%10);
	}

	bool north(Dir dir){
		return dir>=6;
	}
	bool south(Dir dir){
		return dir<3;
	}
	bool west(Dir dir){
		return dir%3 == 0;
	}
	bool east(Dir dir){
		return dir%3 == 2;
	}
}
