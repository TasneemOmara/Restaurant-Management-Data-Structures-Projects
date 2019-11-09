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
	Cook Inservice[];
	Cook Done[];
	int M;
	char** Events;
	int** Event_Data;
	Event** Array;

public:
	//to Read the input file, the following 4 lines must be uncommented
	/*
	Read_File1(int Arr[12]);
	Read_File2(char** Events, int** Event_Data, int M);
	ArrayEnqueuer(Event** Array, char** Events, int** Event_Data, int M);
	QueueEnqueuer(Event** Array, Queue<Event*> EventsQueue, int M);
	*/
	Restaurant(int Cooks_num_val=11);
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void FillDrawingList();

	void main_loop();

	Queue<Cook> get_VI_cooks_queue() const;
	Queue<Cook> get_Vegan_cooks_queue() const;
	Queue<Cook> get_Normal_cooks_queue() const;
	Queue<Cook> get_VI_cooks_break_queue() const;
	Queue<Cook> get_Vegan_cooks_break_queue() const;
	Queue<Cook> get_Normal_cooks_break_queue() const;
	PriorityQueue<Order> get_VI_orders_queue() const;
	Queue<Order> get_Vegan_orders_queue() const;
	LinkedList<Order> get_Normal_orders_list() const;

};
