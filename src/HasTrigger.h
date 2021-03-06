#ifndef HasTrigger_h_
#define HasTrigger_h_

#include "Node.h"
#include "Input.h"
#include "Output.h"
class HasTrigger{
	public:
	HasTrigger(Node * node);
	~HasTrigger();

	Input trigger;
	float triggerThreshold;

	protected:

	bool isTriggerActive();

	private:

	Node * triggerNode;
};
#endif
