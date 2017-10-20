#include "object.h"

void Object::draw(RenderTarget& target, RenderStates states) const{
	states.transform *= getTransform();
	for(auto drawable: drawables)
		target.draw(*drawable, states);
	for(auto child: children)
		target.draw(*child, states);
}

void Object::addChild(Object* child){
	children.push_back(child);
}

void Object::addDrawable(Drawable* drawable){
	drawables.push_back(drawable);
}

void Object::removeChild(Object* child){
	children.remove(child);
}

void Object::removeDrawable(Drawable* drawable){
	drawables.remove(drawable);
}

void Object::updateChildren(){
	for(auto child: children)
		child->update();
}
