#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"



ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	LinkedList<Order> Normal_Orders = get_Normal_orders_list();
	Queue<Order> Vegan_Orders = get_Vegan_orders_queue();
	PriorityQueue<Order> VI_Orders = get_VI_orders_queue();
	switch (this->OrdType)
	{
	case 0:
		Order O(this->OrderID,this->OrdType, this->OrdDishes,this->OrdMoney, this->EventTime);
		Normal_Orders.InsertBeg(O);
		break;
	case 1:
		Order O(this->OrderID,this->OrdType, this->OrdDishes,this->OrdMoney, this->EventTime);
		Vegan_Orders.enqueue(O);
	case 2:
		Order O(this->OrderID,this->OrdType, this->OrdDishes,this->OrdMoney, this->EventTime);
		VI_Orders.enqueue(O,O.VI_Priority());
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