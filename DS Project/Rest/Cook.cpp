#include "Cook.h"

Cook::Cook(){
};

Cook::Cook(int id_val, ORD_TYPE type_val, double speed_val, double dishes_before_break_val, int break_duration_val, int current_time_val) : ID{ id_val }, type{ type_val }, speed{ speed_val }, dishes_before_break{ dishes_before_break_val }, break_duration{ break_duration_val }, current_time{ current_time_val }
{
	dishes_served = 0;
	timeEnteredBreak = 0;
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

double Cook::getDishesServed() const
{
	return dishes_served;
}
//setting and getting the order assigned to the cook

void Cook::AssignOrder(Order &O)
{
	cooking = O;
	dishes_served = dishes_served + cooking.GetDishes();
}

Order& Cook::getAssignedOrder()
{
	return cooking;
}

void Cook::RemoveOrder()
{
/*	Order* p = & (this -> cooking);

	//Set p to hold NULL
	p = NULL;
*/	

	//this->cooking.~Order();
	
	
	Order deleto;
	deleto.setStatus(DONE);
	this->cooking = deleto;
	deleto.~Order();
	

//	this -> cooking = *p;
/*	Order* p = & this -> cooking;
	Order O();
*/
}

void Cook::setMaxCooksNum(int max)
{
	max_cooks_num=max;
}

void Cook::global_time(int i)
{
	current_time = i;
}

//moving the assigned order from in service to done 

bool Cook::ToDone(Cook Arr_done[])
{
	if (current_time >= cooking.get_SV() + (cooking.GetDishes() / speed) )
	{
		cout << "Noooo" << (cooking.GetDishes() / speed) <<endl;
		Arr_done[ID] = *this;
		return true;
	}
	return false;
}


//should he take a break or not 

bool Cook::break_time() const
{	
	if (dishes_served >= dishes_before_break)
	{
		return true;
	}
	return false;
}

void Cook::ResetDishesServed()
{
	dishes_served = 0;
}

void Cook::set_breakDuration(int n)
{
	break_duration = n;
}

void Cook::set_timeEnteredBreak(int steps)
{
	timeEnteredBreak = steps;
}

void Cook::reset_timeEnteredBreak()
{
	timeEnteredBreak = 0;
}

int Cook::get_timeEnteredBreak() const
{
	return timeEnteredBreak;
}

int Cook::get_breakDuration() const
{
	return break_duration;
}