#pragma once
#include "Event.h"

//class for the Promotion event
class PromotionEvent : public Event
{
private:
	int ExtraMoney;

public:
	PromotionEvent();
	PromotionEvent(int eTime, int oID, int ExtraMoney);
	void Execute(Restaurant* pRest);
};

