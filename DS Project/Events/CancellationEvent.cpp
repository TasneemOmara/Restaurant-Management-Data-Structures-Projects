#include "CancellationEvent.h"
#include "Restaurant.h"


CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{
	
}

void CancellationEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

}
