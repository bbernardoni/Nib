#pragma once

#include "../core/object.h"
#include "../core/machine.h"
#include "../res.h"
#include <vector>

class VectObj: public Object {
public:
	VectObj(Game& game, const Model& model);
	virtual ~VectObj(){}

	virtual void preDraw();

	const Model& getModel();
	const vector<Vector2i>& getAnimNibsOff();

protected:
	void draw(RenderTarget& target, RenderStates states) const;

	Vector2f subToScreen(Vector2i sub) const;

	Vector2i pos;
	Vector2i vel;

private:
	void fuzzNibs();
	void calcRibs();

	const Model& model;

	vector<Vector2i> animNibsOff;
	vector<Vector2i> fuzzNibsOff;
	vector<VertexArray> ribs;
};
