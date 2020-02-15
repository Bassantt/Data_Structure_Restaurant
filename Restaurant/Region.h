
#include"..\restaurant\Rest\Order.h"
#include "..\restaurant\Rest\Motorcycle.h"
#include "..\restaurant\Generic_DS\Queue.h"
#include "..\restaurant\Generic_DS\LinkedList.h"
#include "PriQueue.h"
#include "..\restaurant\GUI\GUI.h"
#include <iostream>
#include <fstream>



class Region
{
GUI*pGUI;
int TimeStep;
int NormalOrderCount;
int FrozenOrderCount;
string S;
int VIPOrderCount;
int AutoProm;
int AssignedVIPOrd;
int AssignedFrozOrd;
int AssignedNormOrd;
int NormalMotorCount;
int FastMotorCount;
int FrozenMotorCount;
int NormalMotorSpeed;
int FastMotorSpeed;
bool AllOrderServed;
bool toWaitMotors;
int FrozenMotorSpeed;
Queue<Motorcycle*> NormalMotor;
Queue<Motorcycle*> FrozenMotor;
Queue<Motorcycle*> FastMotor;
Queue<Order*>Frozen;
PriQueue<Motorcycle* , int>WaitingMotorNormal;
PriQueue<Motorcycle* , int>WaitingMotorFrozen;
PriQueue<Motorcycle* , int>WaitingMotorFast;
PriQueue<Order* , double>VIP;
LinkedList<Order*>Normal;
Queue<Order*>*FinalOrder;
bool MotorReurn;

public:

Region();
void setGUI(GUI*P);
void promoteNormal(int TS);
void setAutoProm(int p); 
void assigntimes(Order*d,int Speed);
void DeleteOrder(Order*d);
void setFastMotorSpeed(int s); 
void setFrozenMotorSpeed(int s); 
void setNormalMotorSpeed(int s); 
bool Serve(ORD_TYPE R);
void ServeAll(int CurrentTimeStep,bool All);
int getNormalMotorSpeed();
int getFrozenMotorSpeed();
int getFastMotorSpeed();
int getNormOrdCount();
int getVIPOrdCount();
int getFrozenOrdCount();
int getNormalMotorCount();
int getFrozenMotorCount();
int getFastMotorCount();
void setNormalMotorNum(int c,REGION R);
void setFastMotorNum(int c,REGION R);
void setFrozenMotorNum(int c,REGION R);
void addToOrderList();
void IncrementVIPOrders();
void IncrementFrozenOrders();
void IncrementNormalOrders();
int getAssignedVIPOrd();
int getAssignedFrozOrd();
int getAssignedNormOrd();
Queue<Motorcycle*>* getPrevTimeStep();
void setNormalMotor(int I,int speedMotor,STATUS s,REGION R);
void setFrozenMotor(int I,int speedMotor,STATUS s,REGION R);
void setFastMotor(int I,int speedMotor,STATUS s,REGION R);
void Assign(Order*O);
bool GetAllServed();
bool GetEmptyWaitingMotorQueues();
bool promote(int id,double m);
bool Cancell(int id);
void MotorBack(int TS);
void printOutput(ofstream& ofile,double S,double W);
Queue<Order*>* getfinalorders();
void getstring(string&s);
~Region();
};
