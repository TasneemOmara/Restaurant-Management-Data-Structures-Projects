#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
}

Order::~Order()
{
}

int Order::GetID() const 
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDishes(int d)
{
	Dishes = d>0?d:0;
}

int Order::GetDishes() const
{
	return Dishes;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

double Order::GetReceipt() const
{
	totalMoney = Dishes * Price + extra_money;
	return totalMoney;
}

int Order::get_SV() const
{
	return ServTime;
}

void Order::set_SV(int SV) 
{
	ServTime=SV;
}

int Order::get_AV() const
{
	return ArrTime;
}

void Order::set_AV() 
{
	ArrTime=AV;
}

int Order::get_FT() const
{
	return FinishTime;
}

void Order::set_FT(int FT)
{
	FinishTime=FT;
}





