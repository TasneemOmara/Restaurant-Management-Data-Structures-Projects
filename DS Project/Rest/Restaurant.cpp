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


	Cooks_num = Arr[3] + Arr[4] + Arr[5];
	
	//Normal cooks enqueuer
	for (size_t i = 0; i < Arr[3]; i++)
	{
		Cook c(i, TYPE_NRM, Arr[0], Arr[6]);
		Normal_Cooks.enqueue(c);
	}

	//Vegan cooks enqueuer
	for (size_t i = Arr[3] ; i < Arr[4] + Arr[3] ; i++)
	{
		Cook c(i, TYPE_NRM, Arr[1], Arr[7]);
		Vegan_Cooks.enqueue(c);
	}

	//VIP cooks enqueuer
	for (size_t i = Arr[3] + Arr[4] ; i < Arr[5] + Arr[4] + Arr[3] ; i++)
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
	PROG_MODE mode = pGUI -> getProgramMode();

	//initialize time
	int steps = 0;

	// If you want to use the simulation GUI you must call initSimMode() same as the demo mode
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		pGUI->initSimMode();

		while (true)
		{
			steps++;
			main_loop(steps);

			//GUI
			pGUI->updateInterface();
			pGUI->handleSimGUIEvents();
			FillDrawingList(steps);

			pGUI->waitForClick(); //Wait for user click to enter the loop again.
		}
		break;

	case MODE_STEP:
		pGUI->initSimMode();

		while (true)
		{
			steps++;
			main_loop(steps);

			//GUI
			pGUI->updateInterface();
			pGUI->handleSimGUIEvents();
			FillDrawingList(steps);

			pGUI->sleep(1000); //Updates the loop each 1000 milliseconds.
		}
		break;

	case MODE_SLNT:

		while (true /*hna 7war el condition elly lesa ha3melo mn el sticky note*/)
		{
			steps++;
			main_loop(steps);
		}
		break;
	};

}



//////////////////////////////////   Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	//cout << endl << "Current time step is: " << CurrentTimeStep << endl;
	
	Event *pE;
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
			}
		}
	}


	//Demo
	//Vegan
	Order vegan_order;
	while (Vegan_Orders.peekFront(vegan_order) && !Vegan_Cooks.isEmpty())
	{
		Vegan_Orders.dequeue(vegan_order);
		Cook c;
		Vegan_Cooks.dequeue(c);
		c.AssignOrder(vegan_order);
		(c.getAssignedOrder()).set_SV(steps);
		(c.getAssignedOrder()).setStatus(SRV);
		Inservice[c.GetID()] = c;
	}

	
	//Normal
	Order Normal_Order;
	while (Normal_Orders.getCount() > 0 && !Normal_Cooks.isEmpty())
	{
		Normal_Orders.getbeg(Normal_Order);
		Cook c;
		Normal_Cooks.dequeue(c);
		c.AssignOrder(Normal_Order);
		(c.getAssignedOrder()).set_SV(steps);
		(c.getAssignedOrder()).setStatus(SRV);
		Inservice[c.GetID()] = c;
	}
	

	//VIP
	Order VIP_Order;
	while (VI_Orders.peekFront(VIP_Order) && !VI_Cooks.isEmpty())
	{
		VI_Orders.dequeue(VIP_Order);
		Cook c;
		VI_Cooks.dequeue(c);
		c.AssignOrder(VIP_Order);
		(c.getAssignedOrder()).set_SV(steps);
		(c.getAssignedOrder()).setStatus(SRV);
		Inservice[c.GetID()] = c;
	}
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
	//Printing Current Time to the GUI status bar
	pGUI->printStringInStatusBar("Current Time: " + std::to_string(steps));


	int count_g;
	int count_n = Normal_Orders.getCount();
	int count_v;
	Order* g = Vegan_Orders.toArray(count_g);	//Vegan
	Order* n = Normal_Orders.toArray();			//Normal
	Order* v = VI_Orders.toArray(count_v);      //VIP

	//This is where GUI No's are cooked
	//Waiting Orders
	for (int i = 0 ; i < count_g ; i++)
	{	//Vegan Waiting
		pGUI->addGUIDrawable(new VeganGUIElement(g[i].GetID(), GUI_REGION::ORD_REG));
	}
	for (int i = 0 ; i < count_n ; i++)
	{	//Normal Waiting
		pGUI->addGUIDrawable(new NormalGUIElement(n[i].GetID(), GUI_REGION::ORD_REG));
	}
	for (int i = 0; i < count_v; i++)
	{	//VI Waiting
		pGUI->addGUIDrawable(new VIPGUIElement(v[i].GetID(), GUI_REGION::ORD_REG));
	}

	



	//Serving Printing
	for (int i = 0; i < Cooks_num; i++)
	{
		if (Inservice[i].getAssignedOrder() != 0)
		{
			pGUI->addGUIDrawable(new NormalGUIElement(Inservice[i].getAssignedOrder().GetID(), GUI_REGION::SRV_REG));
		}
	}

	//Done Printing
	for (int i = 0; i < Cooks_num; i++)
	{
		if (Done[i].getAssignedOrder() != 0)
		{
			pGUI->addGUIDrawable(new NormalGUIElement(Done[i].getAssignedOrder().GetID(), GUI_REGION::DONE_REG));
		}
	}
}