#include "PromotionEvent.h"
#include "..\restaurant\Rest\Restaurant.h"


PromotionEvent::PromotionEvent(int t,int i,double au):Event(t,i)
{
	id=i;
	Exmoney = au;
}
double PromotionEvent::getExmon()
{
	return Exmoney;

}

void PromotionEvent::Execute(Restaurant *pRest)
{

	pRest->A.promote(id, Exmoney);
	pRest->B.promote(id, Exmoney);
	pRest->C.promote(id, Exmoney);
	pRest->D.promote(id, Exmoney);


}	//override execute function
PromotionEvent::~PromotionEvent(void)
{
}