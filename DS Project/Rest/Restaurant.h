#pragma once
#include <iostream>

#include "../Defs.h"
#include "../GUI/GUI.h"
#include "../Generic_DS/Node.h"
#include "../Generic_DS/LinkedList.h"
#include "../Generic_DS/PriorityQueue.h"
#include "../Generic_DS/Queue.h"
#include "Order.h"
#include "Cook.h"
#include "../Events/Event.h"
#include "../GUI/GUI.h"
#include "../GUI/GUIDefs.h"


// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	Queue<Cook> VI_Cooks;
	Queue<Cook> Vegan_Cooks;
	Queue<Cook> Normal_Cooks;
	Queue<Cook> VI_Cooks_break;
	Queue<Cook> Vegan_Cooks_break;
	Queue<Cook> Normal_Cooks_break;
	PriorityQueue<Order> VI_Orders;
	Queue<Order> Vegan_Orders;
	LinkedList<Order> Normal_Orders;
	int Cooks_num; 
	int Cooks_num_Vegan;
	int Cooks_num_VIP;
	int Cooks_num_Normal;
	Cook *Inservice;
	Cook *Done;
	Queue<Order> All_Done;
	int m;


public:


	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void FillDrawingList(int steps);

	void main_loop(int x);
	void updateServiceDone(int steps);
	void AssignVIP(int steps);
	void AssignVegan(int steps);
	void AssignNormal(int steps);
	int get_m();
	void moveCookToBreak(Cook &c);
	void moveCookToQueue(Cook &c);


	Queue<Cook>& get_VI_cooks_queue();
	Queue<Cook>& get_Vegan_cooks_queue();
	Queue<Cook>& get_Normal_cooks_queue();
	Queue<Cook>& get_VI_cooks_break_queue();
	Queue<Cook>& get_Vegan_cooks_break_queue();
	Queue<Cook>& get_Normal_cooks_break_queue();
	PriorityQueue<Order>& get_VI_orders_queue();
	Queue<Order>& get_Vegan_orders_queue();
	LinkedList<Order>& get_Normal_orders_list();
	Queue<Order>& get_All_Done();

};
