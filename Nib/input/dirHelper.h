#pragma once

enum Dir { SW, S, SE, W, C, E, NW, N, NE};

namespace DirHelper {
	Dir getDir(int hori, int vert);

	int getHori(Dir dir);
	int getVert(Dir dir);

	Dir flip(Dir dir);
	Dir rotateCW(Dir dir);
	Dir rotateCCW(Dir dir);

	bool north(Dir dir);
	bool south(Dir dir);
	bool west(Dir dir);
	bool east(Dir dir);
};
