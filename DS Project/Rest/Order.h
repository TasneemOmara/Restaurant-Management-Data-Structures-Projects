#pragma once

#include "../Defs.h"
#include <iostream>
#include <cmath>
using namespace std;

class Order
{

protected:
	int ID;                             //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;	                	//order type: Normal, Vegan, VIP
	ORD_STATUS status;	                //waiting, in-service, done
	int Dishes;	                        //The number of dishes in that order            
	double totalMoney;	                //Total order money
	double Price;                       //the total price for one dish
	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	int extra_money;                    //money for promtion if exist (normal orders only )

public:
	Order();
	Order(int ID, ORD_TYPE r_Type, int Dishes_val, double price_val, int ArrTime_val);
	~Order();
	int GetID() const;
	ORD_TYPE GetType() const;
	void SetDishes(int d);
	int GetDishes() const;
	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	double GetReceipt();
	int get_SV() const;
	void set_SV(int SV);
	int get_AV() const;
	void set_AV(int AV);
	int get_FT() const;
	void set_FT(int FT);
	bool to_be_promoted(int extra);
    void set_price(int n);
	int VI_Priority();
	bool operator == (int rhs_id);
	
friend ostream& operator<<(ostream& out, const Order& d)
{
	cout << "The order's ID is " << d.GetID() << " It's type is" << d.GetType() << " It's size is " << d.GetDishes() << "\nIt's status is " << d.getStatus() << endl;
	return out;
}

};
