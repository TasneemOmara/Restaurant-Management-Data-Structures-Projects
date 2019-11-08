#include <iostream>
#include "ArrivalEvent.h"


int main()
{
    Queue<Event*> q1;
    ArrivalEvent *e1 = new ArrivalEvent(0,0,TYPE_NRM);
    q1.enqueue(e1);

    ArrivalEvent *e2 = new ArrivalEvent{0,0,TYPE_VIP};
    ArrivalEvent *e3 = new ArrivalEvent{1,1,TYPE_VIP};
    Event** array_e= new Event*[10];
    array_e[0]=e1;
    
    
    return 0;
}
