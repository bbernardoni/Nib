#include "textInput.h"

char TextInput::text = 0;

void TextInput::update(){
	val = text;
}

void TextInput::reset(){
	text = 0;
}

void TextInput::set(char c){
	text = c;
}
