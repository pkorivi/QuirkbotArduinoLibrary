#ifndef List_h_
#define List_h_

#include "Bot.h"
#include "Node.h"
#include "Input.h"
#include "Output.h"
#include "Streams.h"
#include "CollectionNode.h"

class List:
public CollectionNode<float>,
public InputOutputStream<float>
{
	public:
	
	List():
	InputOutputStream<float>
		(index, value){
		registerInput(index);
		selected = NULL;

		index = 0;
		
	};

	Input<float> index;
	Output<float> value;
	
	protected:

	void onInternalInputChange(BaseInput &input);

	private:

	Input<float> * selected;
};

void List::onInternalInputChange(BaseInput &input){
	if(&input == &index){
		if(items.size()){
			int i = floor(index * items.size()); 
			if(i < 0 ) i  = 0;
			if(i > items.size() - 1) i = items.size() - 1;
			if(items[i] != selected){
				selected = items[i];
				value.set(selected->get());
			}
		}
		else{
			selected = NULL;
			value.set(0);
		}		
	}
	else if(&input == selected){
		value.set(selected->get());
	}
};

#endif