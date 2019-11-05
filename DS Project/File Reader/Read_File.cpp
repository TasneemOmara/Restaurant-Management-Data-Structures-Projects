#include <iostream>
#include <fstream>
using namespace std;



int main()
{
	ifstream myfile;
	// replace "dir" with the directory of the file you want to read and make sure the address has no spaces in it and to put the address inside quotation marks
	myfile.open("dir");
	//initiating and array that includes speeds, number, breaks for different cooks types and timesteps for promotion and number of events
	// Arr[12] = {SN, SG, SV, N, G, V, BM, BN, BG, BV, AutoS, M};
	/*
	SN = speed of all normal cooks 
	SG = speed for vegan cooks
	SV = speed for VIP cooks
	N = number of normal cooks
	G = number of vegan cooks
	V = number of VIP cooks
	BM = is the number of meals the cook must do before taking a break
	BN = the break duration in timesteps for normal cooks 
	BG = the break duration in timesteps for vegan ones 
	BV = the break duration in timesteps for VIP cooks.
	AutoS = represent the number of timesteps after which an order is automatically promoted to VIP
	M = represents the number of events following this line
	*/
	int Arr[12];
	for (int i = 0; i < 12; i++)
	{
		myfile >> Arr[i];
	}
	int M = Arr[11];
	char **Events;
	int **Event_Data;
	Events = new char*[M];
	Event_Data = new int* [M];
	for (int i = 0; i < M; i++)
	{
		char Event_Type;
		myfile >> Event_Type;
		switch (Event_Type)
		{
		case 'R':
			Events[i] = new char[2];
			Event_Data[i] = new int[4];
			Events[i][0] = Event_Type;
			myfile >> Event_Data[i][0];
			myfile >> Events[i][1];
			for (int j = 1; j <= 3; j++)
			{
				myfile >> Event_Data[i][j];
			}
			break;
		case 'X':
			Events[i] = new char[1];
			Events[i][0] = Event_Type;
			Event_Data[i] = new int[2];
			myfile >> Event_Data[i][0];
			myfile >> Event_Data[i][1];
			break;
		case 'P':
			Events[i] = new char[1];
			Events[i][0] = Event_Type;
			Event_Data[i] = new int[3];
			for (int j = 0; j <= 2; j++)
			{
				myfile >> Event_Data[i][j];
			}
			break;
		}
	}	
	
	myfile.close();
	return 0;

}