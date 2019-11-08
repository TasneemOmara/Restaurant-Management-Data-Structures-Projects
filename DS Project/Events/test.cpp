#include <iostream>
#include "ArrivalEvent.h"


int main()
{
    Queue<Event*> q1;
    ArrivalEvent *e1 = new ArrivalEvent(0,0,TYPE_NRM);
    q1.enqueue(e1);
    
    return 0;
}
