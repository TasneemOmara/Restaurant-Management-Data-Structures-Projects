#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "../Events/ArrivalEvent.h"
#include "../Events/CancellationEvent.h"
#include "../File Reader/reader.h"

Restaurant::Restaurant()
{
	
	int M;
	int steps = 1;
	int Arr[12];
	pGUI = NULL;
	Read_File1(Arr);
	M = Arr[11];
	char** Events = new char* [M];
	int** Event_Data = new int* [M];
	Event** Array = new Event * [M];
	Read_File2(Events, Event_Data, M);
	ArrayEnqueuer(Array, Events, Event_Data, M);
	QueueEnqueuer(Array, EventsQueue, M);
	Event* A;
	cout << "We are in restaurant" << boolalpha << EventsQueue.peekFront(A) << endl;
	Cooks_num = Arr[3] + Arr[4] + Arr[5];
	for (size_t i = 0; i < length; i++)
	{

	}
	Inservice = new Cook[Cooks_num];
	Done = new Cook[Cooks_num];
	
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
		{
			pE->Execute(this);
			EventsQueue.dequeue(pE);	//remove event from the queue
		}
	}
	delete pE;		//deallocate event object from memory

}


void Restaurant::main_loop(int steps)
{
	ExecuteEvents(steps);
	bool done=false;
	for (int i = 0; i < Cooks_num; i++)
	{
		if (Inservice[i].getAssignedOrder()!=0)
		{
			Inservice[i].global_time(steps);
			done= Inservice[i].ToDone(Done);
			if (done)
			{
				(Done[i].getAssignedOrder()).set_FT(steps);
				(Done[i].getAssignedOrder()).setStatus(DONE);
			}
		}
	}
	Order vegan_order;
	Vegan_Orders.dequeue(vegan_order);
	Cook c;
	VI_Cooks.dequeue(c);
	c.AssignOrder(vegan_order);
	(c.getAssignedOrder()).set_SV(steps);
	(c.getAssignedOrder()).setStatus(SRV);
	Inservice[c.GetID()]=c;

}

Queue<Cook>& Restaurant::get_VI_cooks_queue()
{
	return VI_Cooks;
}
Queue<Cook>& Restaurant::get_Vegan_cooks_queue()
{
	return Vegan_Cooks;
}
Queue<Cook>& Restaurant::get_Normal_cooks_queue()
{
	return Normal_Cooks;
}
Queue<Cook>& Restaurant::get_VI_cooks_break_queue()
{
	return VI_Cooks_break;
}
Queue<Cook>& Restaurant::get_Vegan_cooks_break_queue()
{
	return Vegan_Cooks_break;
}
Queue<Cook>& Restaurant::get_Normal_cooks_break_queue()
{
	return Normal_Cooks_break;
}

PriorityQueue<Order>& Restaurant::get_VI_orders_queue()
{
	return VI_Orders;
}
Queue<Order>& Restaurant::get_Vegan_orders_queue()
{
	return Vegan_Orders;
}
LinkedList<Order>& Restaurant::get_Normal_orders_list()
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
