#include "trigBoolInput.h"

TrigBoolInput::TrigBoolInput(Trigger trigger){
	trig = trigger;
}
    
void TrigBoolInput::update(){
	bool cur = getState();
	switch(trig){
		case level: val = cur; break;
		case rise: val = cur && !last; break;
		case fall: val = !cur && last; break;
	}
	last = cur;
}

