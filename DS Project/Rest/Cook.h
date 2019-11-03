#pragma once

#include "Defs.h"
#include "Order.h"

class Cook
{
	int ID;
	ORD_TYPE type;	              //for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		              //dishes it can prepare in one clock tick (in one timestep)
	int dishes_before_break;      //dishes he make before the cooks takes break
	Order cooking;                //the order he cooks now
	int max_cooks_num;            //the maximum number of cooks for a specific type
	int current_time;             //universal time stamp
	int dishes_served;            //number to store the served dishes 
	

public:
	Cook(int id_val, ORD_TYPE type_val, int speed_val, int dishes_before_break_val);
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	void setOrderCooking(Order O);
	Order getOrderCooking() const;
	void setMaxCooksNum(int max);
	void global_time(int i);
	bool ToDone(Cook Arr[]);
	bool break_time();
};
