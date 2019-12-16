#include "Rest\Restaurant.h"
#include "GUI\GUIDrawables\NormalGUIElement.h"
#include "GUI\GUIDrawables\VeganGUIElement.h"
#include "GUI\GUIDrawables\VIPGUIElement.h"
#include "GUI\GUI.h"
#include "Events/Event.h"


int main()
{
	//byefta7 el ma7al
	Restaurant* pRest = new Restaurant();

	//Choosing Simulation Mode
	pRest->RunSimulation();
}