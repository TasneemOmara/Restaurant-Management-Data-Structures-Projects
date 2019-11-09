#include <iostream>
#include "ArrivalEvent.h"
#include "../File Reader/reader.h"


int main()
{
    Queue<Event*> q1;
    ArrivalEvent *e1 = new ArrivalEvent(0,0,TYPE_NRM);
    q1.enqueue(e1);

    ArrivalEvent *e2 = new ArrivalEvent{0,0,TYPE_VIP};
    ArrivalEvent *e3 = new ArrivalEvent{1,1,TYPE_VIP};
    Event** array_e= new Event*[10];
    for (size_t i = 0; i < 10; i++)
    {
        array_e[i]= new ArrivalEvent{0,0,TYPE_VIP};
    }
    
    
    
    
    return 0;
}
