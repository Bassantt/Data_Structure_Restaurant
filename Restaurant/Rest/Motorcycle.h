#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	int OrdID;
    ORD_TYPE Ordtype;	//for each order type there is a corresponding motorcycle type 
	Motor_TYPE Motortype;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	int TimeBack;

public:
	Motorcycle();
	void SetMotorType(Motor_TYPE M);
	Motor_TYPE getMotorType();
	void setTimeback(int TB);
	int getTimeback();
	void setspeed(int s);
	int getspeed();
	void SetID(int I);
	int getID();
	void SetOrdType(ORD_TYPE I);
	ORD_TYPE getOrdType();
	void SetOrdID(int I);
	int getOrdID();
	void setstatus(STATUS i);
	void setRegion(REGION i);
	virtual ~Motorcycle();
};

#endif