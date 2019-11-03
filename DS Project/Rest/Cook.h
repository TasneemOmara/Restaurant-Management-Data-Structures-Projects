#pragma once

#include "..\Defs.h"
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
	int breakTime;  // the number of dishes served after break
	

public:
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	void setOrderCooking(Order O);
	void getOrderCooking(Order O);
	void setMacxooksNum(int max);
	void global_time();
	bool ToDone(int Arr[]);
	void set_max_cooks_num(int n);

};
