#include <iostream>
#include <cmath>
#include "Order.h"

int Weight_function(Order VI){
    int AV=VI.get_AV();
    int money=VI.GetReceipt();
    int size=VI.GetDishes();
    return exp(1/AV)+ 5*(money/size);
}