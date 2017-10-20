#pragma once

#include "../core/object.h"
#include <vector>
#include <fstream>

struct PlayerModel {
	PlayerModel(const std::string &filename);

	vector<Vector2i> nibs;
	vector<vector<size_t>> sibs;
	Shader shader;

private:
	size_t addNib(Vector2i nib);
};
