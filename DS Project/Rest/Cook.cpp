#include "Cook.h"


Cook::Cook(int id_val, ORD_TYPE type_val, int speed_val, int dishes_before_break_val, int current_time_val): ID{id_val}, type{type_val}, speed{speed_val}, dishes_before_break{dishes_before_break_val}, current_time{current_time_val}
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
	dishes_served=dishes_served+cooking.GetDishes();
}

Order Cook::getOrderCooking() const
{
	return cooking;
}

void Cook::setMaxCooksNum(int max)
{
	max_cooks_num=max;
}

void Cook::global_time(int i)
{
	current_time=i;
}

//moving the assigned order from in service to done 

bool Cook::ToDone(Cook Arr_done[])
{
	if (current_time==cooking.get_SV()+(cooking.GetDishes()/speed))
	{
		Arr_done[ID]=*this;
		return true;
	}
	return false;
}


//should he take a break or not 

bool Cook::break_time()
{	
	if (dishes_served>=dishes_before_break)
	{
		return true;
	}
	return false;
}

int Cook::getSpeed() const
{
	return speed;
}

bool Order::operator == (int rhs_id)
{
	return this->GetID()==rhs_id;
}

ostream& operator<<(ostream& out, const Cook& d)
{
	cout << "The cook's ID is " << d.GetID() << "he cooks type " << d.GetType() << " his speed is" << d.getSpeed() << "he cooks the order " << d.getOrderCooking() << endl;
	return out;
}
