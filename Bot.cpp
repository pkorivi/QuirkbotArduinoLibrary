#include "Bot.h"


Vector <Node *> Bot::nodes = Vector<Node *>();
Vector <Updatable *> Bot::updatables = Vector<Updatable *>();
volatile unsigned long Bot::frames = 0;
volatile unsigned long Bot::dtMicros = 0;
volatile unsigned long Bot::micros = 0;
volatile unsigned long Bot::millis = 0;
volatile float Bot::seconds = 0;

void Bot::addNode(Node * node){
	if(Bot::nodePosition(node) != -1) return;
	Bot::nodes.push(node);
}
void Bot::removeNode(Node * node){
	if(Bot::nodePosition(node) == -1) return;
	Bot::nodes.pop(node);
}
int Bot::nodePosition(Node * node){
	for(unsigned int i=0; i<Bot::nodes.size(); i++){
		if(Bot::nodes[i] == node) return i;
	}
	return -1;
}

void Bot::addUpdatable(Updatable * updatable){
	if(Bot::updatablePosition(updatable) != -1) return;
	Bot::updatables.push(updatable);
}
void Bot::removeUpdatable(Updatable * updatable){
	if(Bot::updatablePosition(updatable) == -1) return;
	Bot::updatables.pop(updatable);
}
int Bot::updatablePosition(Updatable * updatable){
	for(unsigned int i=0; i<Bot::updatables.size(); i++){
		if(Bot::updatables[i] == updatable) return i;
	}
	return -1;
}

void Bot::update(){
	Bot::frames++;
	Bot::dtMicros = ::micros() - Bot::micros;
	Bot::micros = ::micros();
	Bot::millis = ::millis();
	Bot::seconds = Bot::millis * 0.001;
	
	for(unsigned int i=0; i<Bot::updatables.size(); i++){
		Bot::updatables[i]->update();
	}

	// To make sure keyboar will never jam, do some
	// cleanup every once in a while.
	if(Bot::frames % 1500 == 0){
		if(!pressedKeys.size())
		releaseAllKeys(true);
	}
}
// Keyboard management ---------------------------------------------------------
Vector <uint8_t> Bot::pressedKeys = Vector<uint8_t>();
Vector <uint8_t> Bot::usedKeys = Vector<uint8_t>();
void Bot::pressKey(uint8_t key){
	Keyboard.press(key);
	pressedKeys.push(key);

	bool isNew = true;
	for(uint8_t i = 0; i < usedKeys.size(); i++){
		if(usedKeys[i] == key){
			isNew = false;
		}	break;
	}
	if(isNew){
		usedKeys.push(key);
	}
}
void Bot::releaseKey(uint8_t key){
	Keyboard.release(key);
	pressedKeys.pop(key);

	// Keep it clear
	if(!pressedKeys.size())
		releaseAllKeys();
}
void Bot::releaseAllKeys(bool force){
	//pressedKeys.clear();
	Keyboard.releaseAll();

	if(force){
		Serial.println('c');
		for(uint8_t i = 0; i < usedKeys.size(); i++){
			Keyboard.release(usedKeys[i]);
		}
	}
}

// Utils -----------------------------------------------------------------------
float Bot::map(float x, float inMin, float inMax, float outMin, float outMax){
	float result = ((x - inMin) / (inMax - inMin)) * (outMax - outMin) + outMin;
	if(outMin < outMax){
		if(result < outMin) result = outMin;
		else if(result > outMax) result = outMax;
	}
	else{
		if(result > outMin) result = outMin;
		else if(result < outMax) result = outMax;
	}
	
	return result;
}
float Bot::minimum(float a, float b){
	return min(a,b);
}
float Bot::maximum(float a, float b){
	return max(a,b);
}

int Bot::locationToBackPin(int location){
	switch(location){
		case LL:
			return LLB;
		case RL:
			return RLB;
		case RA:
			return RAB;
		case H:
			return HB;
		case LA:
			return LAB;
		default:
			return NO_LOCATION;
	}
};
int Bot::locationToFrontPin(int location){
	switch(location){
		case LL:
			return LLF;
		case RL:
			return RLF;
		case RA:
			return RAF;
		case H:
			return HF;
		case LA:
			return LAF;
		default:
			return NO_LOCATION;
	}
};