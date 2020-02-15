#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	 double pri;              
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime,WaitTime;	//arrival, service start, and finish times
	
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(int ID, ORD_TYPE r_Type);
	virtual ~Order();
	int getpri();
	int GetID();
	void setRegion(REGION F);
	ORD_TYPE GetType() const;
	REGION GetRegion() const;
	void setarrivaltime(int ArrivalTime);
	void setservingtime(int servingTime);
	void setWaitTime(int W);
	int getserveTime();
	int getWaitTime();
	int getFinishTime();
	void setfinishingtime(int finishingTime);
	int getarrivaltime();
	double gettotalmoney();
	void settype(ORD_TYPE r_Type);
	void settotmon(double m);
	void setid(int i);
    void SetDistance(int d);
	int GetDistance() const;
	Order();
	bool operator==(Order d);
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif