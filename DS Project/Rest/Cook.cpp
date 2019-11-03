#include "Cook.h"


Cook::Cook(int id_val, ORD_TYPE type_val, int speed_val, int dishes_before_break_val, int cook_ID_val): ID{id_val}, type{type_val}, speed{speed_val}, dishes_before_break{dishes_before_break_val}, cook_ID{cook_ID_val}
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

void Cook::setOrderCooking(Order O)
{
	cooking=O;
}

void Cook::setMaxCooksNum(int max)
{
	max_cooks_num=max;
}

void cook::inc_global_time()
{
	current_time+=1;
}