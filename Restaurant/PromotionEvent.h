#pragma once
#include "..\restaurant\events\event.h"
class PromotionEvent :
	public Event
{int id;double Exmoney;
public:
	PromotionEvent(int i,int t,double au);
	~PromotionEvent(void);
	double getExmon();
	void setAutoProm(double a);
	 virtual void Execute(Restaurant *pRest);
};

