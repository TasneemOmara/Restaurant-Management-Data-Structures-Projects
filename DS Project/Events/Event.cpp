#include "Event.h"


Event::Event(){};

int Event::arrival_count = 0;

Event::Event(int eTime, int ordID)
{
	EventTime = eTime;
	OrderID	= ordID;
}


int Event::getEventTime()
{
	return EventTime;
}
int Event::getOrderID()
{
	return OrderID;
}

int Event::get_arrival_count()
{
	return arrival_count;
}

Event::~Event()
{

}

