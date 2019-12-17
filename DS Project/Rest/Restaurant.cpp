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
	m = M;
	char** Events = new char* [M];
	int** Event_Data = new int* [M];
	Event** Array = new Event * [M];
	Read_File2(Events, Event_Data, M);
	ArrayEnqueuer(Array, Events, Event_Data, M);
	QueueEnqueuer(Array, EventsQueue, M);


	Cooks_num = Arr[3] + Arr[4] + Arr[5];
	Cooks_num_Normal = Arr[3];
	Cooks_num_Vegan = Arr[4];
	Cooks_num_VIP = Arr[5];
	

	//Normal cooks enqueuer
	for (size_t i = 0; i < Arr[3]; i++)
	{
		Cook c(i, TYPE_NRM, Arr[0], Arr[6]);
		Normal_Cooks.enqueue(c);
	}

	//Vegan cooks enqueuer
	for (size_t i = Arr[3] ; i < Arr[4] + Arr[3] ; i++)
	{
		Cook c(i, TYPE_VEG, Arr[1], Arr[7]);
		Vegan_Cooks.enqueue(c);
	}

	//VIP cooks enqueuer
	for (size_t i = Arr[3] + Arr[4] ; i < Arr[5] + Arr[4] + Arr[3] ; i++)
	{
		Cook c(i, TYPE_VIP, Arr[2], Arr[8]);
		VI_Cooks.enqueue(c);
	}

	Inservice = new Cook[Cooks_num];
	Done = new Cook[Cooks_num];

	cout << "Normal Cooks : " << endl;
	Queue<Cook>::PrintQueue(Normal_Cooks);
	cout << "Vegan Cooks : " << endl;
	Queue<Cook>::PrintQueue(Vegan_Cooks);
	cout << "VIP Cooks : " << endl;
	Queue<Cook>::PrintQueue(VI_Cooks);

	cout << "Normal Cooks break : " << endl;
	Queue<Cook>::PrintQueue(Normal_Cooks_break);
	cout << "Vegan Cooks break : " << endl;
	Queue<Cook>::PrintQueue(Vegan_Cooks_break);
	cout << "VIP Cooks break : " << endl;
	Queue<Cook>::PrintQueue(VI_Cooks_break);

	cout << "*************************" << endl;
	
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
	cout << "Normal Cooks : " << endl;
	Queue<Cook>::PrintQueue(Normal_Cooks);
	cout << "Vegan Cooks : " << endl;
	Queue<Cook>::PrintQueue(Vegan_Cooks);
	cout << "VIP Cooks : " << endl;
	Queue<Cook>::PrintQueue(VI_Cooks);

	cout << "Normal Cooks break : " << endl;
	Queue<Cook>::PrintQueue(Normal_Cooks_break);
	cout << "Vegan Cooks break : " << endl;
	Queue<Cook>::PrintQueue(Vegan_Cooks_break);
	cout << "VIP Cooks break : " << endl;
	Queue<Cook>::PrintQueue(VI_Cooks_break);

	ExecuteEvents(steps);

	updateServiceDone(steps);
	AssignVIP(steps);
	AssignVegan(steps);
	AssignNormal(steps); 

}

void Restaurant::AssignVIP(int steps)
{
	Order VIP_Order;
	bool foundCookFlag = false;

	while (VI_Orders.peekFront(VIP_Order))
	{
		Cook c;
		if (VI_Cooks.peekFront(c))
		{
			VI_Cooks.dequeue(c);
			if (!(c.break_time()))
			{
				cout << "NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << endl;
				foundCookFlag = true;
			}
			else
			{
				cout << "HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
				moveCookToBreak(c);
			}
		}
		else if (Normal_Cooks.peekFront(c))
		{
			Normal_Cooks.dequeue(c);
			if (!c.break_time())
			{
				foundCookFlag = true;
			}
			else
			{
				moveCookToBreak(c);
			}
		}
		else if (Vegan_Cooks.peekFront(c))
		{
			Vegan_Cooks.dequeue(c);
			if (!c.break_time())
			{
				foundCookFlag = true;
			}
			else
			{
				moveCookToBreak(c);
			}
		}
		if (foundCookFlag)
		{
			VI_Orders.dequeue(VIP_Order);
			c.AssignOrder(VIP_Order);
			c.addDish();
			(c.getAssignedOrder()).set_SV(steps);
			(c.getAssignedOrder()).setStatus(SRV);
			Inservice[c.GetID()] = c;
		}

	}
}

void Restaurant::AssignVegan(int steps)
{
	Order vegan_order;
	bool foundCookFlag = false;
	Cook c;

	while (Vegan_Orders.peekFront(vegan_order) && Vegan_Cooks.peekFront(c))
	{
		Vegan_Cooks.dequeue(c);
		if (!c.break_time())
		{
			foundCookFlag = true;
		}
		else
		{
			moveCookToBreak(c);
		}

		if (foundCookFlag)
		{
			Vegan_Orders.dequeue(vegan_order);
			c.AssignOrder(vegan_order);
			c.addDish();
			(c.getAssignedOrder()).set_SV(steps);
			(c.getAssignedOrder()).setStatus(SRV);
			Inservice[c.GetID()] = c;
		}
	}
}

void Restaurant::AssignNormal(int steps)
{
	Order Normal_Order;
	bool foundCookFlag = false;

	while (Normal_Orders.getCount() > 0)
	{
		Cook c;
		if (Normal_Cooks.peekFront(c))
		{
			Normal_Cooks.dequeue(c);
			if (!c.break_time())
			{
				foundCookFlag = true;
			}
			else
			{
				moveCookToBreak(c);
			}
		}
		else if (VI_Cooks.peekFront(c))
		{
			VI_Cooks.dequeue(c);
			if (!(c.break_time()))
			{
				foundCookFlag = true;
				cout << "NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << endl;
			}
			else
			{
				cout << "HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
				moveCookToBreak(c);
			}
		}
		if (foundCookFlag)
		{
			Normal_Orders.getbeg(Normal_Order);
			c.AssignOrder(Normal_Order);
			c.addDish();
			(c.getAssignedOrder()).set_SV(steps);
			(c.getAssignedOrder()).setStatus(SRV);
			Inservice[c.GetID()] = c;
		}

	}
}

void Restaurant::updateServiceDone(int steps)
{
	bool done = false;

	for (int i = 0; i < Cooks_num; i++)
	{
		if (Inservice[i].getAssignedOrder() != 0)
		{
			Inservice[i].global_time(steps);	//setting current time-stamp to cook
			done = Inservice[i].ToDone(Done);	//check if an order is done by checking if it took enough required time

			if (done)
			{
				(Done[i].getAssignedOrder()).set_FT(steps);		//setting finish time for just-done order
				(Done[i].getAssignedOrder()).set_WT();			//setting total waiting time for done order
				(Done[i].getAssignedOrder()).setStatus(DONE);	//setting the order status as done
				All_Done.enqueue(Done[i].getAssignedOrder());
				Done[i].RemoveOrder();
				moveCookToQueue(Done[i]);
			}
		}
	}
}



void Restaurant::moveCookToBreak(Cook &c)
{
	
		ORD_TYPE CookType = c.GetType();
		if (CookType == TYPE_NRM)
		{
			Normal_Cooks_break.enqueue(c);
		}
		else if (CookType == TYPE_VEG)
		{
			Vegan_Cooks_break.enqueue(c);
		}
		else if (CookType == TYPE_VIP)
		{
			VI_Cooks_break.enqueue(c);
		}

}

void Restaurant::moveCookToQueue(Cook& c)
{
	ORD_TYPE CookType = c.GetType();
	if (CookType == TYPE_NRM)
	{
		Normal_Cooks.enqueue(c);
	}
	else if (CookType == TYPE_VEG)
	{
		Vegan_Cooks.enqueue(c);
	}
	else if (CookType == TYPE_VIP)
	{
		VI_Cooks.enqueue(c);
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

Queue<Order>& Restaurant::get_All_Done()
{
	return All_Done;
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

	int count_g;
	int count_n = Normal_Orders.getCount();
	int count_v;
	int count_ord_all = All_Done.getcounter();

	Order* g = Vegan_Orders.toArray(count_g);	//Vegan
	Order* n = Normal_Orders.toArray();			//Normal
	Order* v = VI_Orders.toArray(count_v);      //VIP
	Order* d = All_Done.toArray(m);				//All Done


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
	for (int i = 0 ; i < count_v; i++)
	{	//VI Waiting
		pGUI->addGUIDrawable(new VIPGUIElement(v[i].GetID(), GUI_REGION::ORD_REG));
	}


	//Serving Printing
	for (int i = 0 ; i < Cooks_num; i++)
	{
		if (Inservice[i].getAssignedOrder() != 0)
		{
			pGUI->addGUIDrawable(new NormalGUIElement(Inservice[i].getAssignedOrder().GetID(), GUI_REGION::SRV_REG));
		}
	}

	//Done Printing
	for (int i = 0 ; i < m ; i++)
	{
		{
			pGUI->addGUIDrawable(new NormalGUIElement(d[i].GetID(), GUI_REGION::DONE_REG));
			//cout << Done[i].getAssignedOrder().GetID() << " " << Done[i].getAssignedOrder().get_WT() << endl;
		}
	}



	//Calculating Averages
	double SV_tot = 0;
	double WT_tot = 0;
	double AVG_SV = 0;
	double AVG_WT = 0;

	for (int i = 0; i < m; i++)
	{
		SV_tot	= SV_tot + d[i].get_SV();
		WT_tot	= WT_tot + d[i].get_WT();
		cout << d[i].get_WT();
	}
	cout << endl;
	
	if (count_ord_all != 0)
	{
		AVG_SV = SV_tot / count_ord_all;
		AVG_WT = WT_tot / count_ord_all;
	}


	//Printing Statistics to the GUI status bar
		/*Printing Current Time*/
	pGUI->printStringInStatusBar("Current Time: "		+ std::to_string(steps) + "\n"

		/*Orders Printing*/
		+ "Orders: " + std::to_string(count_ord_all)	+ "	[Norm:" + std::to_string(count_n)
		+ ", Veg:" + std::to_string(count_v)
		+ ", VIP:" + std::to_string(count_n)
		+ "]" + "\n"

		/*Cooks Printing*/
		+ "Cooks: " + std::to_string(Cooks_num)			+ "	[Norm:" + std::to_string(count_n)
		+ ", Veg:" + std::to_string(count_v)
		+ ", VIP:" + std::to_string(count_n)
		+ "]" + "\n"

		/*Average Time Printing*/
		+ "Avg Wait = " + std::to_string(AVG_WT) + ",	Avg Serv = " + std::to_string(AVG_SV) + "\n"

		/*Auto Promoted Printing*/
		+ "Auto-Promoted: " + std::to_string(/*Auto Promoted*/ 1000000001)	);

}

int Restaurant::get_m()
{
	return m;
};