#include "ArrivalEvent.h"
#include "../Rest/Restaurant.h"

static int arrival_count = 0;

ArrivalEvent::ArrivalEvent(){};
ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
	arrival_count++;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	// This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	// cout << endl << this -> OrdType << "zidan" <<endl;
	switch (this->OrdType)
	{
	case 0:
		{
		Order O1(this->OrderID, this->OrdType, this->OrdDishes, this->OrdMoney, this->EventTime);
		pRest->get_Normal_orders_list().InsertEnd(O1);
		break;
		}
	case 1:
		{
		Order O2(this->OrderID, this->OrdType, this->OrdDishes, this->OrdMoney, this->EventTime);
		pRest->get_Vegan_orders_queue().enqueue(O2);
		break;
		}
	case 2:
		{
		Order O3(this->OrderID, this->OrdType, this->OrdDishes, this->OrdMoney, this->EventTime);
		pRest->get_VI_orders_queue().enqueue(O3,O3.VI_Priority());
		break;
		}
	}

}


void ArrivalEvent::setDishes(int size)
{
	OrdDishes = size;
}

void ArrivalEvent::setMoney(double money)
{
	OrdMoney = money;
}

int ArrivalEvent::get_arrival_count()
{
	return arrival_count;
}