#include "Cook.h"


Cook::Cook(int id_val, ORD_TYPE type_val, int speed_val, int dishes_before_break_val): ID{id_val}, type{type_val}, speed{speed_val}, dishes_before_break{dishes_before_break_val}
{
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

//setting and getting the order assigned to the cook

void Cook::setOrderCooking(Order O)
{
	cooking=O;
}

Order Cook::getOrderCooking(Order O) const
{
	return cooking;
}

void Cook::setMaxCooksNum(int max)
{
	max_cooks_num=max;
}

void cook::global_time(int i)
{
	current_time=i;
}

//moving the assigned order from in service to done 

bool cook::ToDone(int Arr_done[])
{
	if (current_time==cooking.get_SV()+(cooking.GetDishes()/speed))
	{
		Arr_done[ID]=*this;
		return true;
	}
	return false;
}