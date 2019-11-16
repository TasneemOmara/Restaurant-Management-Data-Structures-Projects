#pragma once

#include "Event.h"



//class for the Cancellation event
class CancellationEvent: public Event
{
	//info about the order ralted to arrival event
	//int OrdDishes;	//order number of dishes
	//double OrdMoney;	//Total order money
public:
	CancellationEvent();
	CancellationEvent(int eTime, int oID);
	virtual void Execute(Restaurant* pRest);	//override execute function


};

