#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

using namespace std;
using namespace sf;

struct Model {
	Model(const std::string &filename);

	vector<Vector2i> nibs;
	vector<vector<size_t>> sibs;
	Shader shader;

private:
	size_t addNib(Vector2i nib);
};
