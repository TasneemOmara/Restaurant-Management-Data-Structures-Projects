#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "../Events/ArrivalEvent.h"


Restaurant::Restaurant(int Cooks_num_val)
{
	pGUI = NULL;

	Inservice[Cooks_num_val];
	Done[Cooks_num_val];
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getProgramMode();
		
	// If you want to use the simulation GUI you must call initSimMode() same as the demo mode
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		pGUI->initSimMode();
		break;
	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


void Restaurant::main_loop(int x)
{
	int mouse_click = x;
	ExecuteEvents(mouse_click);
	for (size_t i = 0; i < Cooks_num; i++)
	{
		Inservice[i].global_time(mouse_click);
		Inservice[i].ToDone(Done);
		(Done[i].getAssignedOrder()).set_FT(mouse_click);
	}
	Order v;
	Vegan_Orders.dequeue(v);
	Cook c;
	VI_Cooks.dequeue(c);
	c.AssignOrder(v);
	(c.getAssignedOrder()).set_SV(mouse_click);
	Inservice[c.GetID()]=c;

}

Queue<Cook> Restaurant::get_VI_cooks_queue() const
{
	return VI_Cooks;
}
Queue<Cook> Restaurant::get_Vegan_cooks_queue() const
{
	return Vegan_Cooks;
}
Queue<Cook> Restaurant::get_Normal_cooks_queue() const
{
	return Normal_Cooks;
}
Queue<Cook> Restaurant::get_VI_cooks_break_queue() const
{
	return VI_Cooks_break;
}
Queue<Cook> Restaurant::get_Vegan_cooks_break_queue() const
{
	return Vegan_Cooks_break;
}
Queue<Cook> Restaurant::get_Normal_cooks_break_queue() const
{
	return Normal_Cooks_break;
}

PriorityQueue<Order> Restaurant::get_VI_orders_queue() const
{
	return VI_Orders;
}
Queue<Order> Restaurant::get_Vegan_orders_queue() const
{
	return Vegan_Orders;
}
LinkedList<Order> Restaurant::get_Normal_orders_list() const
{
	return Normal_Orders;
}

Restaurant::~Restaurant()
{
		delete pGUI;
}


void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for cooks)

}
