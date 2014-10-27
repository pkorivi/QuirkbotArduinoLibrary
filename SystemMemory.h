#ifndef Profile_h_
#define Profile_h_

#include "Bot.h"
#include "Node.h"
#include "HasInterval.h"
#include "HasOut.h"
#include "Output.h"

class SystemMemory :
public Node,
public HasInterval,
public HasOut<float>
{
	public:

	SystemMemory():
	HasInterval
		(this),
	HasOut<float>
		(this){
		interval = 0.01;
	};

	void onInterval();

	private:

	static int getFreeRam();

};
int SystemMemory::getFreeRam(){
	extern int __heap_start, *__brkval; 
	int v; 
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
void SystemMemory::onInterval(){
	out.set(getFreeRam());
}

#endif