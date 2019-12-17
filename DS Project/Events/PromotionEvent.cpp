#include "PromotionEvent.h"
#include "../Rest/Restaurant.h"

PromotionEvent::PromotionEvent(){};
PromotionEvent::PromotionEvent(int eTime, int oID,int exMoney) : Event(eTime, oID)
{
	ExtraMoney = exMoney;
}

void PromotionEvent::Execute(Restaurant* pRest)
{	
	Order* promo;
	promo = pRest->get_Normal_orders_list().getorder(this->OrderID);
	//bool found = pRest->get_Normal_orders_list().Find(this->OrderID, *promo);
	promo->to_be_promoted(ExtraMoney);
	pRest->get_VI_orders_queue().enqueue(*promo , promo->VI_Priority());
	pRest->get_Normal_orders_list().DeleteNode(this->OrderID);
	/*		
	Order O3(this->OrderID,this->OrdType, this->OrdDishes,this->OrdMoney, this->EventTime);
	pRest->get_VI_orders_queue().enqueue(O3,O3.VI_Priority());
	*/

}