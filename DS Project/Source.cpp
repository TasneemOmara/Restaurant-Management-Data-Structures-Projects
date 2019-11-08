#include "Rest\Restaurant.h"

#include "GUI\GUIDrawables\NormalGUIElement.h"
#include "GUI\GUIDrawables\VeganGUIElement.h"
#include "GUI\GUIDrawables\VIPGUIElement.h"
#include "GUI\GUI.h"


int main() {

	const int time = 0;

	//byefta7 el ma7al
	Restaurant* pRest = new Restaurant;

	//Choosing Simulation Mode
	pRest->RunSimulation();

	//Executes ALL events that should take place at current timestep
	//pRest->ExecuteEvents(int CurrentTimeStep);

	//This should add ALL orders and cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for cooks)
	pRest->FillDrawingList();

	delete pRest;

	//Creating GUI & Initializing
	GUI gui;
	gui.initSimMode();

	int& steps = x;

	while (true) {
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
}