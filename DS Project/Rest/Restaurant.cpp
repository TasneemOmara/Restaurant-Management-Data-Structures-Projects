#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "../Events/ArrivalEvent.h"
#include "../Events/CancellationEvent.h"
#include "../File Reader/reader.h"
#include "../Generic_DS/Queue.h"

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
	//cout << "We are in restaurant" << boolalpha << EventsQueue.peekFront(A) << endl;
	Cooks_num = Arr[3] + Arr[4] + Arr[5];
	
	//
	for (size_t i = 0; i < Arr[3]; i++)
	{
		Cook c(i, TYPE_NRM, Arr[0], Arr[6]);
		Normal_Cooks.enqueue(c);
	}

	//Vegan cooks enqueuer
	for (size_t i = Arr[3] + 1 ; i < Arr[4]; i++)
	{
		Cook c(i, TYPE_NRM, Arr[1], Arr[7]);
		Vegan_Cooks.enqueue(c);
	}

	//VIP cooks enqueuer
	for (size_t i = Arr[3] + Arr[4] + 1 ; i < Arr[5]; i++)
	{
		Cook c(i, TYPE_NRM, Arr[2], Arr[8]);
		VI_Cooks.enqueue(c);
	}

	Inservice = new Cook[Cooks_num];
	Done = new Cook[Cooks_num];
	
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	// << pGUI << endl;
	PROG_MODE mode = pGUI->getProgramMode();

	// If you want to use the simulation GUI you must call initSimMode() same as the demo mode
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		pGUI->initSimMode();
		break;
	case MODE_STEP:
		pGUI->initSimMode();
		break;
	case MODE_SLNT:
		pGUI->initSimMode();
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
	cout << endl << "Current time step is" << CurrentTimeStep << endl;
	Event *pE;
	//cout << endl << EventsQueue.peekFront(pE) << endl;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if (pE->getEventTime() == CurrentTimeStep)	//no more events at current time
		{
			pE->Execute(this);
			EventsQueue.dequeue(pE);	//remove event from the queue
		}
		else break;
	}
	//delete pE;		//deallocate event object from memory

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
				cout << endl << Done[i].getAssignedOrder() << endl;
			}
		}
	}

	Order vegan_order;
	if (Vegan_Orders.dequeue(vegan_order))
	{
		Cook c;
		Vegan_Cooks.dequeue(c);
		c.AssignOrder(vegan_order);
		(c.getAssignedOrder()).set_SV(steps);
		(c.getAssignedOrder()).setStatus(SRV);
		Inservice[c.GetID()] = c;
		cout << c.getAssignedOrder() << endl;
	}

	pGUI -> updateInterface();
	pGUI -> handleSimGUIEvents();


	// For Interactive mode
	FillDrawingList(steps);
	pGUI->waitForClick();

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

//This function should be implemented in phase1
//It should add ALL orders and cooks to the drawing list
//It should get orders from orders lists/queues/stacks/whatever (same for cooks)
void Restaurant::FillDrawingList(int steps)
{
	Queue<Order> testvegan = get_Vegan_orders_queue();
	Order* p = testvegan.toArray();
	testvegan.PrintQueue(testvegan);
	
	if (p != nullptr) {
		cout << endl << "of zero" << p[0].GetID() << endl;
	}
	cout << p[0];

	if (steps % 5 == 0)
	{
		pGUI->printStringInStatusBar("Current Time: " + std::to_string(steps));
	}

	//This is where GUI No's are cooked
	for (int i = 0; i <= steps; i++)
	{
		//p[i].GetID()
		//Waiting Up-left corner
		pGUI->addGUIDrawable(new VIPGUIElement(i, GUI_REGION::ORD_REG));
		//pGUI->addGUIDrawable(new NormalGUIElement(i, GUI_REGION::COOK_REG));
		//pGUI->addGUIDrawable(new VeganGUIElement(i, GUI_REGION::SRV_REG));
		pGUI->addGUIDrawable(new VIPGUIElement(i, GUI_REGION::DONE_REG));
	}
}