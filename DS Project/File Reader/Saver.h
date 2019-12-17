#pragma once
#include <iostream>
#include <fstream>
#include "../Events/ArrivalEvent.h"
#include "../Events/Event.h"
#include "../Generic_DS/Queue.h"
#include "../Events/CancellationEvent.h"
#include "../Events/PromotionEvent.h"
#include "../Defs.h"
#include "../Rest/Restaurant.h"

using namespace std;

//class Restaurant;

void Save(Restaurant* pRest)
{
	ofstream savedfile("Output.txt");
	savedfile << "FT";
	savedfile << "	";
	savedfile << "ID";
	savedfile << "	";
	savedfile << "AT";
	savedfile << "	";
	savedfile << "WT";
	savedfile << "	";
	savedfile << "ST\n";
	pRest->get_All_Done();
	
};