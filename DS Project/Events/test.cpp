#include "../Generic_DS/Queue.h"
#include "Event.h"
#include "ArrivalEvent.h"
#include "../Defs.h"
#include "CancellationEvent.h"
#include "../Rest/Restaurant.h"
#include <iostream>
#include <fstream>
#include "../File Reader/reader.h"

using namespace std;

int main()
{
    /*Queue<Event*> q1;
    ArrivalEvent *e1 = new ArrivalEvent(0,0,TYPE_NRM);
    q1.enqueue(e1);

    ArrivalEvent *e2 = new ArrivalEvent{0,0,TYPE_VIP};
    ArrivalEvent *e3 = new ArrivalEvent{1,1,TYPE_VIP};
    Event** array_e= new Event*[10];
    for (size_t i = 0; i < 10; i++)
    {
        array_e[i]= new ArrivalEvent{0,0,TYPE_VIP};
    }*/

    int Arr[12];
	Read_File1(Arr);
	int M = Arr[11];
	char** Events = new char* [M];
	int** Event_Data = new int* [M];
	Read_File2(Events, Event_Data, M);
    
    
    
    
    
    return 0;
}
