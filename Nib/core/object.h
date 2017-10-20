#pragma once

#include <SFML/Graphics.hpp>
#include <list>
using namespace std;
using namespace sf;

class Game;

class Object: public Drawable, public Transformable {
public:
	Object(Game& game): game(game) {}
	virtual ~Object(){}

	virtual void update(){}

protected:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	void addChild(Object* child);
	void addDrawable(Drawable* drawable);
	void removeChild(Object* child);
	void removeDrawable(Drawable* drawable);

	void updateChildren();

	Game& game;

	list<Object*> children;
	list<Drawable*> drawables;
};
