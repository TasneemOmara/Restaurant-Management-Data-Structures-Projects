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
	
	
	//Printing Statistics
	int count_ord_all = pRest -> get_All_Done().getcounter();		//Orders
	int count_n = 0;												//Norm Ord
	int count_g = 0;												//Vegan Ord
	int count_v = 0;												//VIP Ord

	//For calculating Averages
	double ST_tot = 0;
	double WT_tot = 0;
	double AVG_ST = 0;
	double AVG_WT = 0;

	int k = pRest->count_for_arrivals;
	cout << "this is K" << k << endl;
	Order o;

	while ( pRest->get_All_Done().dequeue(o) )
	{
		switch (o.GetType())

		{
		case TYPE_NRM:
			count_n++;
			break;
		case TYPE_VEG:
			count_g++;
			break;
		case TYPE_VIP:
			count_v++;
			break;
		}
	}
	Order *Q = pRest->get_All_Done().toArray(k);
	Queue<Order> All_Done;
	pRest->get_All_Done().PrintQueue(All_Done);
	cout << "K = " << k << endl;
	cout << "count_ord_all = " << count_ord_all << endl;
	

	for (int i = 0; i < k ; i++)
	{
		ST_tot = ST_tot + Q[i].get_ST();
		WT_tot = WT_tot + Q[i].get_WT();
	}

	if (count_ord_all != 0)
	{
		AVG_ST = ST_tot / count_ord_all;
		AVG_WT = WT_tot / count_ord_all;
	}

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
	//int all_count = pRest->get_All_Done().getcounter();
	Order* d = pRest->get_All_Done().toArray(k);
	for (int i = 0; i < k; i++)
	{
		savedfile << d[i].get_FT();
		savedfile << "	";
		savedfile << d[i].GetID();
		savedfile << "	";
		savedfile << d[i].get_AV();
		savedfile << "	";
		savedfile << d[i].get_WT();
		savedfile << "	";
		savedfile << d[i].get_ST();
		savedfile << "\n";
	}
	savedfile << "..................................................\n";
	savedfile << "..................................................\n";
	savedfile << "Orders: " << count_ord_all << " [Norm:" << count_n++ << ", Veg: " << count_g << ", VIP: " << count_v << " ]\n";
	savedfile << "cooks: " << pRest->get_Cooks_num_Normal() + pRest->get_Cooks_num_Vegan() + pRest->get_Cooks_num_VIP() 
		<<"   [Norm:"<< pRest->get_Cooks_num_Normal() << ", Veg:" << pRest->get_Cooks_num_Vegan() << ", VIP:" 
		<< pRest->get_Cooks_num_VIP() << "]\n";
	savedfile << "Avg Wait = " << AVG_WT << ", Avg Serv = " << AVG_ST << "\n";
	savedfile << "Auto-promoted: " << pRest->get_count_p() << "\n";




};