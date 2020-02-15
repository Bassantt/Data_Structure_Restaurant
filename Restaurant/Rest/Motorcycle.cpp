#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}


void Motorcycle::setspeed(int s)
{
	 speed=s;
}
void Motorcycle::SetID(int I)
{
	ID=I;
}
int Motorcycle::getID()
{
	return ID;
}
void Motorcycle::SetOrdID(int I)
{
	OrdID=I;
}
int Motorcycle::getOrdID()
{
	return OrdID;
}
void Motorcycle::SetOrdType(ORD_TYPE I)
{
	Ordtype=I;

}
ORD_TYPE Motorcycle::getOrdType()
{
	return Ordtype;
}
int Motorcycle::getspeed()
{
	return speed;
}
void Motorcycle::setTimeback(int TB)
{
	TimeBack=TB;
}
int Motorcycle::getTimeback()
{
	return TimeBack;
}
void Motorcycle::setRegion(REGION i)
{
	 region=i;
}
void Motorcycle::SetMotorType(Motor_TYPE M)
{
	Motortype=M;
}
Motor_TYPE Motorcycle::getMotorType()
{
	return Motortype;
}
void Motorcycle::setstatus(STATUS i)
{
	 status=i;
}
Motorcycle::~Motorcycle()
{
}
