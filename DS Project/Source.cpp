#include "Rest\Restaurant.h"
#include "GUI\GUIDrawables\NormalGUIElement.h"
#include "GUI\GUIDrawables\VeganGUIElement.h"
#include "GUI\GUIDrawables\VIPGUIElement.h"
#include "GUI\GUI.h"
#include "Events/Event.h"


int main() {

	//byefta7 el ma7al
	Restaurant* pRest = new Restaurant();
	int steps = 0;

	//Choosing Simulation Mode
	pRest->RunSimulation();

	//Creating GUI & Initializing

	while (true)
	{
		pRest->main_loop(steps);
		steps++;
	}
}