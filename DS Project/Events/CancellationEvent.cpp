#include "CancellationEvent.h"
#include "../Rest/Restaurant.h"

CancellationEvent::CancellationEvent() {};
CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{
	
}

void CancellationEvent::Execute(Restaurant* pRest)
{
	bool found = pRest->get_Normal_orders_list().DeleteNode(this->OrderID); //errors may rise due to operator overloading
}
