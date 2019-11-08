#include "CancellationEvent.h"
#include "Restaurant.h"


CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{
	
}

void CancellationEvent::Execute(Restaurant* pRest)
{
	bool found = pRest->get_Normal_orders_list().DeleteNode(ID); //errors may rise due to operator overloading

}
