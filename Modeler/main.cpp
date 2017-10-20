#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;

#define SCALE 144
#define POINT_RAD 5.0f
#define WIN_WIDTH 1600
#define WIN_HEIGHT 900
#define READ
string filename = "player.mod";

/* Controls
A: add mode
S: slide mode
D: delete mode
C: copy mode
Left/Right: move layer
R: reset zoom to 1600 mode
F: reset zoom to 1920 mode (my fullscreen mode)
L: set layer to loop
H: hide circles
Z: scale/zoom model
Shft: align to x/y vals

LMouse: perform mode action
RMouse: set origin
Scroll: scroll zoom

*/

enum CmdState {add, slide, del, cpy} cmdState;
size_t arrI = 0;
int scale = SCALE;
int slidePoint = -1;
int zoomScale = -1;

void printState(){
	string cmdStr;
	switch(cmdState){
	case add:
		cmdStr = "add mode";
		break;
	case slide:
		cmdStr = "slide mode";
		break;
	case del:
		cmdStr = "delete mode";
		break;
	case cpy:
		cmdStr = "copy mode";
		break;
	}
	string info = cmdStr + ", arrI=" + to_string(arrI) + ", scale=" + to_string(scale);
	cout << info << endl;
}

string getPointStr(Vector2i point){
	return "(" + to_string(point.x) + "," + to_string(point.y) + ")";
}

Vector2i getPos(vector<vector<Vector2i>>& arrs, Vector2i mpos){
	Vector2i pos = scale*(mpos-Vector2i(WIN_WIDTH/2, WIN_HEIGHT/2));
	for(size_t i=0; i<arrs.size(); i++){
		for(size_t j=0; j<arrs[i].size(); j++){
			if(cmdState == slide && slidePoint == j && Mouse::isButtonPressed(Mouse::Left) && i == arrI)
				continue;
			Vector2f diff = Vector2f(pos - arrs[i][j])/(float)SCALE;
			if(diff.x*diff.x + diff.y*diff.y < POINT_RAD*POINT_RAD){
				return arrs[i][j];
			}
		}
	}
	if(Keyboard::isKeyPressed(Keyboard::LShift)||Keyboard::isKeyPressed(Keyboard::RShift)){
		for(size_t i=0; i<arrs.size(); i++){
			for(size_t j=0; j<arrs[i].size(); j++){
				if(cmdState == slide && slidePoint == j && Mouse::isButtonPressed(Mouse::Left) && i == arrI)
					continue;
				Vector2f diff = Vector2f(pos - arrs[i][j])/(float)SCALE;
				if(abs(diff.x) < POINT_RAD) pos.x = arrs[i][j].x;
				if(abs(diff.y) < POINT_RAD) pos.y = arrs[i][j].y;
			}
		}
	}
	if(pos.x < -WIN_WIDTH /2*SCALE) pos.x = -WIN_WIDTH /2*SCALE;
	if(pos.x >  WIN_WIDTH /2*SCALE) pos.x =  WIN_WIDTH /2*SCALE;
	if(pos.y < -WIN_HEIGHT/2*SCALE) pos.y = -WIN_HEIGHT/2*SCALE;
	if(pos.y >  WIN_HEIGHT/2*SCALE) pos.y =  WIN_HEIGHT/2*SCALE;
	return pos;
}

int main()
{
	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Modeler", Style::Close|Style::Titlebar);
	printState();
	VertexArray curH(Lines, 2);
	VertexArray curV(Lines, 2);
	VertexArray centH(Lines, 2);
	VertexArray centV(Lines, 2);
	vector<vector<Vector2i>> arrs;
	vector<bool> looped;
	arrs.push_back(vector<Vector2i>());
	looped.push_back(false);
	cmdState = add;
	bool hideCir = false;

	curH[0].color = curH[1].color = curV[0].color = curV[1].color = Color(64, 64, 64);
	centH[0].color = centH[1].color = centV[0].color = centV[1].color = Color(128, 128, 128);
	centH[0].position = Vector2f(WIN_WIDTH/2.0f-10, WIN_HEIGHT/2.0f);
	centH[1].position = Vector2f(WIN_WIDTH/2.0f+10, WIN_HEIGHT/2.0f);
	centV[0].position = Vector2f(WIN_WIDTH/2.0f, WIN_HEIGHT/2.0f-10);
	centV[1].position = Vector2f(WIN_WIDTH/2.0f, WIN_HEIGHT/2.0f+10);

#ifdef READ
	{
		ifstream inF(filename);
		size_t arrsSize;
		inF >> arrsSize;
		arrs.clear();
		looped.clear();
		for(size_t i=0; i<arrsSize; i++){
			size_t arrSize;
			bool arrLooped;
			inF >> arrSize >> arrLooped;
			vector<Vector2i> arr;
			arr.resize(arrSize);
			for(size_t j=0; j<arrSize; j++){
				int xCoord, yCoord;
				inF >> xCoord >> yCoord;
				arr[j] = Vector2i(xCoord, yCoord);
			}
			arrs.push_back(arr);
			looped.push_back(arrLooped);
		}
		inF.close();
	}
#endif

	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed){
				if(event.key.code == Keyboard::A){
					cmdState = add;
					printState();
				}
				if(event.key.code == Keyboard::S){
					cmdState = slide;
					printState();
				}
				if(event.key.code == Keyboard::D){
					cmdState = del;
					printState();
				}
				if(event.key.code == Keyboard::C){
					cmdState = cpy;
					printState();
				}
				if(event.key.code == Keyboard::Left && arrI > 0){
					if(arrs[arrI].size() == 0){
						arrs.erase(arrs.begin() + arrI);
						looped.erase(looped.begin() + arrI);
					}
					arrI--;
					printState();
				}
				if(event.key.code == Keyboard::Right){
					if(arrs[arrI].size() > 0){
						if(arrI == arrs.size()-1){
							arrs.push_back(vector<Vector2i>());
							looped.push_back(false);
						}
						arrI++;
					} else {
						if(arrI < arrs.size()-1){
							arrs.erase(arrs.begin() + arrI);
							looped.erase(looped.begin() + arrI);
						}
					}
					printState();
				}
				if(event.key.code == Keyboard::R){
					scale = SCALE;
					printState();
				}
				if(event.key.code == Keyboard::F){
					scale = 120;
					printState();
				}
				if(event.key.code == Keyboard::L){
					looped[arrI] = !looped[arrI];
				}
				if(event.key.code == Keyboard::H){
					hideCir = !hideCir;
				}
				if(event.key.code == Keyboard::Z){
					if(zoomScale < 0){
						zoomScale = scale;
						cout << "init zoom scale to " << zoomScale << endl;
					} else {
						for(size_t i=0; i<arrs.size(); i++){
							for(size_t j=0; j<arrs[i].size(); j++){
								arrs[i][j] = arrs[i][j]*scale/zoomScale;
							}
						}
						cout << "model scaled from " << zoomScale << " to " << scale << endl;
						zoomScale = -1;
					}
				}
			}
			if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
				Vector2i mpos(event.mouseButton.x, event.mouseButton.y);
				Vector2i pos = scale*(mpos-Vector2i(WIN_WIDTH/2, WIN_HEIGHT/2));
				if(cmdState == add){
					pos = getPos(arrs, mpos);
					cout << "add point ";
					arrs[arrI].push_back(pos);
				} else if(cmdState == slide){
					slidePoint = -1;
					for(size_t i=0; i<arrs[arrI].size(); i++){
						Vector2f diff = Vector2f(pos - arrs[arrI][i])/(float)SCALE;
						if(diff.x*diff.x + diff.y*diff.y < POINT_RAD*POINT_RAD){
							slidePoint = i;
							break;
						}
					}
				} else if(cmdState == del){
					for(size_t i=0; i<arrs[arrI].size(); i++){
						Vector2f diff = Vector2f(pos - arrs[arrI][i])/(float)SCALE;
						if(diff.x*diff.x + diff.y*diff.y < POINT_RAD*POINT_RAD){
							cout << "delete point " << getPointStr(arrs[arrI][i]) << endl;
							for(i++; i<arrs[arrI].size(); i++){
								arrs[arrI][i-1] = arrs[arrI][i];
							}
							arrs[arrI].resize(arrs[arrI].size()-1);
							break;
						}
					}
				} else if(cmdState == cpy){
					for(size_t i=0; i<arrs[arrI].size(); i++){
						Vector2f diff = Vector2f(pos - arrs[arrI][i])/(float)SCALE;
						if(diff.x*diff.x + diff.y*diff.y < POINT_RAD*POINT_RAD){
							arrs[arrI].resize(arrs[arrI].size()+1);
							for(size_t j=arrs[arrI].size()-1; i<j-1; j--){
								arrs[arrI][j] = arrs[arrI][j-1];
							}
							if(arrs[arrI].size() > i+2){
								arrs[arrI][i+1] = (arrs[arrI][i]+arrs[arrI][i+2])/2;
							} else {
								arrs[arrI][i+1] = arrs[arrI][i] + Vector2i(int(POINT_RAD*SCALE*3), int(POINT_RAD*SCALE*3));
							}
							cout << "insert point " << getPointStr(arrs[arrI][i+1]) << endl;
							break;
						}
					}
				}
			}
			if(event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left
					&& cmdState == slide && slidePoint >= 0){
				cout << "slide point " << getPointStr(arrs[arrI][slidePoint]) << endl;
			}
			if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right){
				Vector2i mpos(event.mouseButton.x, event.mouseButton.y);
				Vector2i pos = getPos(arrs, mpos);
				for(size_t i=0; i<arrs.size(); i++){
					for(size_t j=0; j<arrs[i].size(); j++){
						arrs[i][j] -= pos;
					}
				}
			}
			if(event.type == Event::MouseWheelScrolled){
				scale -= 12*int(event.mouseWheelScroll.delta);
				printState();
			}
		}

		Vector2i pos = getPos(arrs, Mouse::getPosition(window));
		Vector2f spos = ((Vector2f)pos)/(float)SCALE + Vector2f(WIN_WIDTH/2.0f, WIN_HEIGHT/2.0f);
		if(cmdState == slide && slidePoint >= 0 && slidePoint < (int)arrs[arrI].size() && Mouse::isButtonPressed(Mouse::Left)){
			arrs[arrI][slidePoint] = pos;
		}

		curH[0].position = Vector2f(0.0f, spos.y);
		curH[1].position = Vector2f((float)WIN_WIDTH, spos.y);
		curV[0].position = Vector2f(spos.x, 0.0f);
		curV[1].position = Vector2f(spos.x, (float)WIN_HEIGHT);
		window.setTitle("Modeler: ("+to_string(pos.x)+","+to_string(pos.y)+")");

		window.clear();
		Transform scaling;
		scaling.scale(SCALE/(float)scale, SCALE/(float)scale, WIN_WIDTH/2.0f, WIN_HEIGHT/2.0f);
		RenderStates renderStates(scaling);

		window.draw(curH, renderStates);
		window.draw(curV, renderStates);
		window.draw(centH, renderStates);
		window.draw(centV, renderStates);
		for(size_t i=0; i<arrs.size(); i++){
			VertexArray arr(LinesStrip, arrs[i].size()+looped[i]);
			Color c = (i == arrI)? Color::Green: Color::White;
			for(size_t j=0; j<arrs[i].size(); j++){
				arr[j].position = ((Vector2f)arrs[i][j])/(float)SCALE + Vector2f(WIN_WIDTH/2.0f, WIN_HEIGHT/2.0f);
				arr[j].color = c;
				if(!hideCir){
					CircleShape point(POINT_RAD);
					point.setPosition(arr[j].position-Vector2f(POINT_RAD, POINT_RAD));
					point.setFillColor(c);
					window.draw(point, renderStates);
				}
			}
			if(looped[i]){
				arr[arrs[i].size()].position = arr[0].position;
				arr[arrs[i].size()].color = c;
			}
			window.draw(arr, renderStates);
		}
		window.display();
	}

	ofstream outF(filename);
	outF << arrs.size() << endl;
	for(size_t i=0; i<arrs.size(); i++){
		outF << arrs[i].size() << " " << looped[i] << endl;
		for(size_t j=0; j<arrs[i].size(); j++){
			Vector2i pos = arrs[i][j];
			outF << pos.x << " " << pos.y << endl;
		}
	}
	outF.close();

	return 0;
}