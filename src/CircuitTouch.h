#ifndef CircuitTouch_h_
#define CircuitTouch_h_

#include "CommonNodeIncludes.h"

#define QB_CIRCUIT_TOUCH_MAX_TIME 10000
#define QB_CIRCUIT_TOUCH_DISCHARGE_TIME 1000

class CircuitTouch :
public Node,
public Updatable,
public HasOut
{
	public:

	CircuitTouch();
	~CircuitTouch();

	Input place;
	Input min;
	Input max;
	Input sensitivity;

	void update();

	protected:

	void onInternalInputChange(BaseInput &internalInput);

	UpperFilter upper;
	LowPassFilter filter;

	unsigned int frontPin;
	unsigned int backPin;
	unsigned long startTime;
	unsigned long deadlineTime;
	bool measuring;
};
#endif
