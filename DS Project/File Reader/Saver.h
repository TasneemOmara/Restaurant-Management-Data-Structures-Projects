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
	//int m = pRest->get_m();
	int all_count = pRest->get_All_Done().getcounter();
	Order* d = pRest->get_All_Done().toArray(all_count);
	for (int i = 0; i < all_count; i++)
	{
		savedfile << d[i].get_FT();
		savedfile << "	";
		savedfile << d[i].GetID();
		savedfile << "	";
		savedfile << d[i].get_AV();
		savedfile << "	";
		savedfile << d[i].get_WT();
		savedfile << "	";
		savedfile << d[i].get_SV();
		savedfile << "\n";
	}
	
};