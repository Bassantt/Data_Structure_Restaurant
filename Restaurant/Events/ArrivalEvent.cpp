#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg,int d,double m):Event(eTime, oID)
{
	OrdType = oType;
	if(reg==0)
	OrdRegion = A_REG;
	else if(reg==1)
	OrdRegion = B_REG;
	else if(reg==2)
	OrdRegion = C_REG;
	else 
	OrdRegion = D_REG;
	OrdMoney=m;
	OrdDistance=d;

}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	Order *NewOrder=new Order(OrderID,OrdType);
	NewOrder->SetDistance(OrdDistance);
	NewOrder->setarrivaltime(EventTime);
	NewOrder->settotmon(OrdMoney);
	NewOrder->setRegion(OrdRegion);
	if(OrdRegion==A_REG)
	{
		pRest->A.Assign(NewOrder);
	}
	else if(OrdRegion==B_REG)
	{
		pRest->B.Assign(NewOrder);
	}
	else if(OrdRegion==C_REG)
	{
		pRest->C.Assign(NewOrder);
	}
	else
	{
		pRest->D.Assign(NewOrder);
	}

}
