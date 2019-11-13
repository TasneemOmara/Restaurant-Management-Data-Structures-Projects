#include "Rest\Restaurant.h"

#include "GUI\GUIDrawables\NormalGUIElement.h"
#include "GUI\GUIDrawables\VeganGUIElement.h"
#include "GUI\GUIDrawables\VIPGUIElement.h"
#include "GUI\GUI.h"
#include "File Reader/reader.h"
#include "Events/Event.h"

int main() {

	int M;
	int steps = 1;
	int Arr[12];
	Queue<Event*> EventsQueue;

	//to Read the input file, the following 4 lines must be uncommented
	
	Read_File1(Arr);
	M = Arr[11];
	char** Events = new char* [M];
	int** Event_Data = new int* [M];
	Event** Array = new Event* [M];
	Read_File2(Events, Event_Data, M);
	ArrayEnqueuer(Array, Events, Event_Data, M);
	QueueEnqueuer(Array, EventsQueue, M); 
	

	/*
	//byefta7 el ma7al
	Restaurant* pRest = new Restaurant(EventsQueue);

	//Choosing Simulation Mode
	pRest->RunSimulation();



	pRest->main_loop(steps);

	//This should add ALL orders and cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for cooks)
	pRest->FillDrawingList();

	delete pRest;

	//Creating GUI & Initializing
	GUI gui;
	gui.initSimMode();

	while (true)
	{
		if (steps % 5 == 0) {
			gui.printStringInStatusBar("Current Time: " + std::to_string(steps));
		}


		//This is where GUI No's are cooked
		for (int i = 0; i < steps; i++) {
			gui.addGUIDrawable(new VIPGUIElement(i + 5, GUI_REGION::ORD_REG));
			gui.addGUIDrawable(new NormalGUIElement(i, GUI_REGION::COOK_REG));
			gui.addGUIDrawable(new VeganGUIElement(i, GUI_REGION::SRV_REG));
			gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::DONE_REG));
		}

		gui.updateInterface();
		gui.handleSimGUIEvents();

		// For Interactive mode
		gui.waitForClick();

		// For step-by-step mode
		//gui.sleep(1000);

		steps++;
	}
	*/

}