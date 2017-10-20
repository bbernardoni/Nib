#include "game.h"

Game::Game():
	Object(*this),
	player(*this),
	ground(Vector2f(1600,5))
{
	srand((unsigned int)time(NULL));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	win.create(VideoMode(1600, 900), "Nib", Style::Default, settings);
	win.setFramerateLimit(60);
	frame = 0;

	player.setPosition(100, 200);
	addChild(&player);

	ground.setPosition(0, 800);
	addDrawable(&ground);
}

Game::~Game(){
}

void Game::update(){
	TextInput::reset();
	
	Event event;
	while(win.pollEvent(event)){
		if(event.type == Event::Closed){
			win.close();
		}
		else if(event.type == Event::TextEntered){
			if(event.text.unicode < 128)
				TextInput::set(event.text.unicode);
		}
	}
	InputBase::updateAll();

	updateChildren();

	win.clear();
	win.draw(*this);
	win.display();

	frame++;
}

bool Game::isRunning(){
	return win.isOpen();
}

Vector2u Game::getWinSize(){
	return win.getSize();
}

Res& Game::getRes(){
	return res;
}

GameInput& Game::getInput(){
	return gIn;
}

int Game::getFrame(){
	return frame;
}