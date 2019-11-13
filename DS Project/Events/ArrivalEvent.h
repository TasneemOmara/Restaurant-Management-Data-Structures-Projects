#pragma once

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDishes;	//order number of dishes
	ORD_TYPE OrdType;		//order type: Normal, Vegan, VIP	                
	double OrdMoney;	//Total order money
public:
    ArrivalEvent();
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);	
	virtual void Execute(Restaurant *pRest);	//override execute function
	virtual void setDishes(int size);
	virtual void setMoney(double money);


};