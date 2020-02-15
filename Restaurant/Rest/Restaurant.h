#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_
#include"..\Region.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Generic_DS\Queue.h"
#include"String"
#include "..\Events\ArrivalEvent.h"
#include "..\CancellationEvent.h"
#include "..\PromotionEvent.h"
#include <fstream>
#include "..\Rest\Motorcycle.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	string PrevOrders;
	string nameoffile;
	int AutoS;
	GUI *pGUI;
	Queue<Motorcycle*>*PrevTimeStepMotors;
	bool IncrementTimeStep;
	Queue<Event*> EventsQueue;	
	PriQueue<Order*,double>*FinOrder;
	double WaitA;
	double WaitB;
	double WaitC;
	double WaitD;
	double ServA;
	double ServB;
	double ServC;
	double ServD;
	double WaitRest;
	double ServeRest;
	
public:
	Region A,B,C,D;
	void PrintAtSatusBar(int &CurrentTimeStep);
	void Read();
	void stepbystep();
	Restaurant();
	void InterActive();
	void Silent();
	void Update();
	int getautos();
	void SetFinalPriQueue();
	void increaseOrderCount(Order*O);
	void setAutos(int i);
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void DeletefromDrawingarea();
	GUI *getpGUI();
    void printinOutPutFile();
	~Restaurant();
    
};

#endif