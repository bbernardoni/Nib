#pragma once

#include "../core/object.h"
#include "../core/machine.h"
#include "../res.h"
#include <vector>

class VectObj: public Object {
public:
	VectObj(Game& game, Model* model);
	virtual ~VectObj(){}

protected:
	void draw(RenderTarget& target, RenderStates states) const;

	void updateChildren();

	int getRand() const;
	Vector2f subToScreen(Vector2i sub) const;

	vector<VertexArray> ribs;
	Model* model;
};
