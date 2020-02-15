#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	pri=totalMoney/(Distance*ArrTime)*1.0;
}
void Order::setRegion(REGION F)
{

Region=F;
}
ORD_TYPE Order::GetType()const {return type;}
REGION Order::GetRegion()const {return Region;}
Order::Order()
{

}
void Order::setWaitTime(int W)
{
WaitTime=W;
}

int Order::getserveTime()
{
	return ServTime;
}
int Order::getWaitTime()
{
	return WaitTime;
}
int Order::getFinishTime()
{
	return FinishTime;
}
void Order::settype(ORD_TYPE r_Type)
{
type = r_Type;
}

Order::~Order()
{
}


bool Order::operator==(Order d)
{
if(ID==d.GetID())
return 1;
else return 0;
}
int Order::getpri(){return pri;}

int Order::GetID()
{
	return ID;
}
void Order::setarrivaltime(int ArrivalTime)
{
ArrTime=ArrivalTime;
}
void Order::setfinishingtime(int finishingingTime)
{
FinishTime=finishingingTime;
}
void Order::setservingtime(int ServingTime)
{
ServTime=ServingTime;
}
int Order::getarrivaltime()
{
	return ArrTime;

}
double Order::gettotalmoney()
{return totalMoney;

}

void Order::settotmon(double m)
{totalMoney=m;

}
void Order::setid(int i)
{
ID=i;

}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}
