#include "model.h"

Model::Model(const std::string &filename)
{
	ifstream inF(filename);
	size_t arrsSize;
	inF >> arrsSize;
	sibs.resize(arrsSize);
	for(size_t i=0; i<arrsSize; i++){
		size_t arrSize;
		bool arrLooped;
		inF >> arrSize >> arrLooped;
		sibs[i].resize(arrSize + arrLooped);

		for(size_t j=0; j<arrSize; j++){
			int xCoord, yCoord;
			inF >> xCoord >> yCoord;
			sibs[i][j] = addNib(Vector2i(xCoord, yCoord));
		}

		if(arrLooped)
			sibs[i][arrSize] = sibs[i][0];
	}
	inF.close();

	shader.loadFromFile("shaders/forward.vert", "shaders/line.geom", "shaders/glow.frag");
	shader.setUniform("thickness", 3.f);
}

size_t Model::addNib(Vector2i nib){
	size_t index;
	for(index=0; index<nibs.size(); index++){
		if(nibs[index] == nib)
			return index;
	}

	nibs.push_back(nib);
	return index;
}