#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;
#include"string"
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant() 
{ 
	IncrementTimeStep=0;
	pGUI = NULL;
	PrevOrders="A B C D";
}

void Restaurant::Read()
{

pGUI->PrintMessage("Please Enter File Name!","","","","");
nameoffile=pGUI->GetString();

//EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

int SN,SF,SV;
int N,F,V;
char EventType;
int ID,TS,DST;
double MON,ExMon;
char Reg;
char TYP;
int AutoS1;
int numofevents;

ifstream file(nameoffile+".txt");
if (file.is_open())
{

	while (!file.eof())
	{
		file >> SN >> SF >> SV;

		for (int i = 0; i < 4; i++)
		{
			file >> N >> F >> V;
			if (i == 0)
			{   A.setNormalMotorSpeed(SN);
			    A.setFrozenMotorSpeed(SF);
			    A.setFastMotorSpeed(SV);
				A.setNormalMotorNum(N,A_REG);
				A.setFrozenMotorNum(F,A_REG);
				A.setFastMotorNum(V,A_REG);
			}
			if (i == 1)
			{ 
			    B.setNormalMotorSpeed(SN);
			    B.setFrozenMotorSpeed(SF);
			    B.setFastMotorSpeed(SV);
				B.setNormalMotorNum(N,B_REG);
				B.setFrozenMotorNum(F,B_REG);
				B.setFastMotorNum(V,B_REG);
			}
			if (i == 2)
			{
			    C.setNormalMotorSpeed(SN);
			    C.setFrozenMotorSpeed(SF);
			    C.setFastMotorSpeed(SV);
				C.setNormalMotorNum(N,C_REG);
				C.setFrozenMotorNum(F,C_REG);
				C.setFastMotorNum(V,C_REG);
			}
			if (i == 3)
			{
			    D.setNormalMotorSpeed(SN);
			    D.setFrozenMotorSpeed(SF);
			    D.setFastMotorSpeed(SV);
				D.setNormalMotorNum(N,D_REG);
				D.setFrozenMotorNum(F,D_REG);
				D.setFastMotorNum(V,D_REG);
			}



		}
		file >> AutoS1;
		setAutos(AutoS1);
		A.setAutoProm(AutoS1);
		B.setAutoProm(AutoS1);
		C.setAutoProm(AutoS1);
		D.setAutoProm(AutoS1);

		file >> numofevents;
		for (int i = 0; i < numofevents; i++)
		{

			file >> EventType;
			if (EventType == 'R')
			{
				file >> TS >> TYP >> ID >> DST >> MON >> Reg;
				if (Reg == 'A')
				{
					if (TYP == 'V')
					{
						Event*m = new ArrivalEvent(TS, ID, TYPE_VIP, A_REG, DST, MON);
						AddEvent(m);
						/*R->A.SetVIPOrder(ID,DST,MON,TS);*/
					}
					//TYPE_NRM,	//normal order
					//TYPE_FROZ
					if (TYP == 'F')
					{
						Event*m = new ArrivalEvent(TS, ID, TYPE_FROZ, A_REG, DST, MON);
						AddEvent(m);
						
					}
					if (TYP == 'N')
					{
						Event*m = new ArrivalEvent(TS, ID, TYPE_NRM, A_REG, DST, MON);
						AddEvent(m);
						
					}
				}
			    if (Reg == 'B')
				{
					if (TYP == 'V')
					{
						Event*m = new ArrivalEvent(TS, ID, TYPE_VIP, B_REG, DST, MON);
						AddEvent(m);
						
					}
					if (TYP == 'F')
					{
						Event*m = new ArrivalEvent(TS, ID, TYPE_FROZ, B_REG, DST, MON);
						AddEvent(m);

						
					}
					if (TYP == 'N')
					{
						Event*m = new ArrivalEvent(TS, ID, TYPE_NRM, B_REG, DST, MON);
						AddEvent(m);

						
					}
				}
				if (Reg == 'C')
				{
					if (TYP == 'V')
					{

						Event*m = new ArrivalEvent(TS, ID, TYPE_VIP, C_REG, DST, MON);
						AddEvent(m);
						
					}
					if (TYP == 'F')
					{
						Event*m = new ArrivalEvent(TS, ID, TYPE_FROZ, C_REG, DST, MON);
						AddEvent(m);
						
					}
					if (TYP == 'N')
					{

						Event*m = new ArrivalEvent(TS, ID, TYPE_NRM, C_REG, DST, MON);
						AddEvent(m);
						
					}
				}
				if (Reg == 'D')
				{
					if (TYP == 'V')
					{

						Event*m = new ArrivalEvent(TS, ID, TYPE_VIP, D_REG, DST, MON);
						AddEvent(m);
						
					}
					if (TYP == 'F')
					{
						Event*m = new ArrivalEvent(TS, ID, TYPE_FROZ, D_REG, DST, MON);
						AddEvent(m);
						
					}
					if (TYP == 'N')
					{

						Event*m = new ArrivalEvent(TS, ID, TYPE_NRM, D_REG, DST, MON);
						AddEvent(m);
						
					}
				}


			}
			if (EventType == 'X')
			{
				file >> TS >> ID;
				Event*m = new CancellationEvent(TS, ID);
				AddEvent(m);
			}
			if (EventType == 'P')
			{

				file >> TS >> ID >> ExMon;
				Event*m = new PromotionEvent(TS, ID, ExMon);
				AddEvent(m);
			}


		}
		break;

	}
}
else
{
	pGUI->PrintMessage("We Can not open the file ! ","" ,"","","");
}
}

void Restaurant::stepbystep()
{
	Read();
	string e;
	int CurrentTimeStep = 1;

	while (!EventsQueue.isEmpty())
	{
	   char timestep[10];
	   itoa(CurrentTimeStep, timestep, 10);
	   ExecuteEvents(CurrentTimeStep);	
       A.promoteNormal(CurrentTimeStep);
	   B.promoteNormal(CurrentTimeStep);
	   C.promoteNormal(CurrentTimeStep);
	   D.promoteNormal(CurrentTimeStep);
       pGUI->UpdateInterface();
       PrintAtSatusBar(CurrentTimeStep);
	   Sleep(2000);
	   A.ServeAll(CurrentTimeStep,false);
	   B.ServeAll(CurrentTimeStep,false);
	   C.ServeAll(CurrentTimeStep,false);
	   D.ServeAll(CurrentTimeStep,false);
	   A.MotorBack(CurrentTimeStep);
	   B.MotorBack(CurrentTimeStep);
	   C.MotorBack(CurrentTimeStep);
	   D.MotorBack(CurrentTimeStep);
       pGUI->UpdateInterface();
       PrintAtSatusBar(CurrentTimeStep);
	   Sleep(2000);
	   	CurrentTimeStep++;
        PrevOrders="Order served in last time step: ";   
		A.getstring(e);
		PrevOrders=PrevOrders+"A: "+e;
		B.getstring(e);
		PrevOrders=PrevOrders+" B: "+e;
		C.getstring(e);
		PrevOrders=PrevOrders+" C: "+e;
		D.getstring(e);
		PrevOrders=PrevOrders+" D: "+e;		

    }
		   CurrentTimeStep--;
     
	while(!A.GetAllServed()||!B.GetAllServed()||!C.GetAllServed()||!D.GetAllServed())
	{
	   CurrentTimeStep++;
	   PrintAtSatusBar(CurrentTimeStep);
	   pGUI->UpdateInterface();
	   Sleep(2000);
	   A.promoteNormal(CurrentTimeStep);
	   B.promoteNormal(CurrentTimeStep);
	   C.promoteNormal(CurrentTimeStep);
	   D.promoteNormal(CurrentTimeStep);
	   A.ServeAll(CurrentTimeStep,true);
	   B.ServeAll(CurrentTimeStep,true);
	   C.ServeAll(CurrentTimeStep,true);
	   D.ServeAll(CurrentTimeStep,true);
	   A.MotorBack(CurrentTimeStep);
	   B.MotorBack(CurrentTimeStep);
	   C.MotorBack(CurrentTimeStep);
	   D.MotorBack(CurrentTimeStep);	   
       pGUI->UpdateInterface();
       PrintAtSatusBar(CurrentTimeStep);
       Sleep(2000);

	    PrevOrders="Order served in last time step: ";   
		A.getstring(e);
		PrevOrders=PrevOrders+"A: "+e;
		B.getstring(e);
		PrevOrders=PrevOrders+" B: "+e;
		C.getstring(e);
		PrevOrders=PrevOrders+" C: "+e;
		D.getstring(e);
		PrevOrders=PrevOrders+" D: "+e;	
		
	}
	while(!A.GetEmptyWaitingMotorQueues()||!B.GetEmptyWaitingMotorQueues()||!C.GetEmptyWaitingMotorQueues()||!D.GetEmptyWaitingMotorQueues())
	{
	   CurrentTimeStep++;
	   A.MotorBack(CurrentTimeStep);
	   B.MotorBack(CurrentTimeStep);
	   C.MotorBack(CurrentTimeStep);
	   D.MotorBack(CurrentTimeStep);
	   Sleep(1000);
       pGUI->UpdateInterface();	
	   PrintAtSatusBar(CurrentTimeStep);
	   PrevOrders="A B C B ";
	}


printinOutPutFile();

}
void Restaurant::SetFinalPriQueue()
{
	ServeRest=0;
	WaitRest=0;
	FinOrder=new PriQueue<Order*,double>;
	double SumWait=0;
	double SumServ=0;
	Queue<Order*>*d;Order *O;
	d=A.getfinalorders();
	while(!d->isEmpty())
	{
		d->dequeue(O);
		SumWait=SumWait+O->getWaitTime();
		SumServ=SumServ+O->getserveTime();
		FinOrder->enqueue(O,-(O->getFinishTime()+O->getserveTime()*.0001));
	}
	ServA=SumServ;
	WaitA=SumWait;
	ServeRest=ServeRest+SumServ;
	WaitRest=WaitRest+SumWait;
	SumWait=0;
	SumServ=0;
	d=B.getfinalorders();
	while(!d->isEmpty())
	{
		d->dequeue(O);
		FinOrder->enqueue(O,-(O->getFinishTime()+O->getserveTime()*.0001));
		SumWait=SumWait+O->getWaitTime();
		SumServ=SumServ+O->getserveTime();
	}
	ServeRest=ServeRest+SumServ;
	WaitRest=WaitRest+SumWait;
	ServB=SumServ;
	WaitB=SumWait;
	SumWait=0;
	SumServ=0;
	d=C.getfinalorders();
	while(!d->isEmpty())
	{
		d->dequeue(O);
		FinOrder->enqueue(O,-(O->getFinishTime()+O->getserveTime()*.0001));
		SumWait=SumWait+O->getWaitTime();
		SumServ=SumServ+O->getserveTime();
	}
	ServeRest=ServeRest+SumServ;
	WaitRest=WaitRest+SumWait;
	ServC=SumServ;
	WaitC=SumWait;
	d=D.getfinalorders();
	while(!d->isEmpty())
	{
		d->dequeue(O);
		FinOrder->enqueue(O,-(O->getFinishTime()+O->getserveTime()*.0001));
		SumWait=SumWait+O->getWaitTime();
		SumServ=SumServ+O->getserveTime();
	}
	ServeRest=ServeRest+SumServ;
	WaitRest=WaitRest+SumWait;
	ServD=SumServ;
	WaitD=SumWait;

}
void Restaurant::increaseOrderCount(Order*O)
{
	REGION R=O->GetRegion();
	if(R==A_REG)
	{
		if(O->GetType()==TYPE_FROZ)
			A.IncrementFrozenOrders();
	    if(O->GetType()==TYPE_NRM)
			A.IncrementNormalOrders();
	    if(O->GetType()==TYPE_VIP)
			A.IncrementVIPOrders();
	}
	if(R==B_REG)
	{
	
		if(O->GetType()==TYPE_FROZ)
			B.IncrementFrozenOrders();
	    if(O->GetType()==TYPE_NRM)
			B.IncrementNormalOrders();
	    if(O->GetType()==TYPE_VIP)
			B.IncrementVIPOrders();
	}
		if(R==C_REG)
	{
	if(O->GetType()==TYPE_FROZ)
			C.IncrementFrozenOrders();
	    if(O->GetType()==TYPE_NRM)
			C.IncrementNormalOrders();
	    if(O->GetType()==TYPE_VIP)
			C.IncrementVIPOrders();
	}
			if(R==D_REG)
	{
	if(O->GetType()==TYPE_FROZ)
			D.IncrementFrozenOrders();
	    if(O->GetType()==TYPE_NRM)
			D.IncrementNormalOrders();
	    if(O->GetType()==TYPE_VIP)
			D.IncrementVIPOrders();
	}
}

void Restaurant::InterActive()
{
	
	Read();
	string e;
	int CurrentTimeStep = 1;

	while (!EventsQueue.isEmpty())
	{
	   char timestep[10];
	   itoa(CurrentTimeStep, timestep, 10);
	   ExecuteEvents(CurrentTimeStep);	
       A.promoteNormal(CurrentTimeStep);
	   B.promoteNormal(CurrentTimeStep);
	   C.promoteNormal(CurrentTimeStep);
	   D.promoteNormal(CurrentTimeStep);
       pGUI->UpdateInterface();
       PrintAtSatusBar(CurrentTimeStep);
	   Sleep(2000);
	   A.ServeAll(CurrentTimeStep,false);
	   B.ServeAll(CurrentTimeStep,false);
	   C.ServeAll(CurrentTimeStep,false);
	   D.ServeAll(CurrentTimeStep,false);
	   A.MotorBack(CurrentTimeStep);
	   B.MotorBack(CurrentTimeStep);
	   C.MotorBack(CurrentTimeStep);
	   D.MotorBack(CurrentTimeStep);
       pGUI->UpdateInterface();
       PrintAtSatusBar(CurrentTimeStep);
	   Sleep(2000);
	   pGUI->PrintMessage("Please Click","","","","");
	   pGUI->waitForClick();
	   	CurrentTimeStep++;
        PrevOrders="Order served in last time step: ";      
		A.getstring(e);
		PrevOrders=PrevOrders+"A: "+e;
		B.getstring(e);
		PrevOrders=PrevOrders+" B: "+e;
		C.getstring(e);
		PrevOrders=PrevOrders+" C: "+e;
		D.getstring(e);
		PrevOrders=PrevOrders+" D: "+e; 		

    }
		   CurrentTimeStep--;
     
	while(!A.GetAllServed()||!B.GetAllServed()||!C.GetAllServed()||!D.GetAllServed())
	{
	   CurrentTimeStep++;
	   PrintAtSatusBar(CurrentTimeStep);
	   pGUI->UpdateInterface();
	   Sleep(2000);
	   A.promoteNormal(CurrentTimeStep);
	   B.promoteNormal(CurrentTimeStep);
	   C.promoteNormal(CurrentTimeStep);
	   D.promoteNormal(CurrentTimeStep);
	   A.ServeAll(CurrentTimeStep,true);
	   B.ServeAll(CurrentTimeStep,true);
	   C.ServeAll(CurrentTimeStep,true);
	   D.ServeAll(CurrentTimeStep,true);
	   A.MotorBack(CurrentTimeStep);
	   B.MotorBack(CurrentTimeStep);
	   C.MotorBack(CurrentTimeStep);
	   D.MotorBack(CurrentTimeStep);	   
       pGUI->UpdateInterface();
       PrintAtSatusBar(CurrentTimeStep);
       Sleep(2000);
	   pGUI->PrintMessage("Please Click","","","","");
	   pGUI->waitForClick();
	    PrevOrders="Order served in last time step: ";   
		A.getstring(e);
		PrevOrders=PrevOrders+"A: "+e;
		B.getstring(e);
		PrevOrders=PrevOrders+" B: "+e;
		C.getstring(e); 
		PrevOrders=PrevOrders+" C: "+e;
		D.getstring(e);
		PrevOrders=PrevOrders+" D: "+e; 
		
	}
	while(!A.GetEmptyWaitingMotorQueues()||!B.GetEmptyWaitingMotorQueues()||!C.GetEmptyWaitingMotorQueues()||!D.GetEmptyWaitingMotorQueues())
	{
	   CurrentTimeStep++;
	   A.MotorBack(CurrentTimeStep);
	   B.MotorBack(CurrentTimeStep);
	   C.MotorBack(CurrentTimeStep);
	   D.MotorBack(CurrentTimeStep);
	   Sleep(1000);
       pGUI->UpdateInterface();	
	   PrintAtSatusBar(CurrentTimeStep);
	   PrevOrders="A B C B ";
	   pGUI->PrintMessage("Please Click","","","","");
	   pGUI->waitForClick();
	}

	Sleep(1000);
	printinOutPutFile();


}

void Restaurant::Silent()
{	
	
	Read();
	string e;
	int CurrentTimeStep = 1;

	while (!EventsQueue.isEmpty())
	{
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		ExecuteEvents(CurrentTimeStep);
		A.promoteNormal(CurrentTimeStep);
		B.promoteNormal(CurrentTimeStep);
		C.promoteNormal(CurrentTimeStep);
		D.promoteNormal(CurrentTimeStep);
		
		A.ServeAll(CurrentTimeStep, false);
		B.ServeAll(CurrentTimeStep, false);
		C.ServeAll(CurrentTimeStep, false);
		D.ServeAll(CurrentTimeStep, false);
		A.MotorBack(CurrentTimeStep);
		B.MotorBack(CurrentTimeStep);
		C.MotorBack(CurrentTimeStep);
		D.MotorBack(CurrentTimeStep);
		
		CurrentTimeStep++;
		
	}
	CurrentTimeStep--;

	while (!A.GetAllServed() || !B.GetAllServed() || !C.GetAllServed() || !D.GetAllServed())
	{
		CurrentTimeStep++;
		
		A.promoteNormal(CurrentTimeStep);
		B.promoteNormal(CurrentTimeStep);
		C.promoteNormal(CurrentTimeStep);
		D.promoteNormal(CurrentTimeStep);
		A.ServeAll(CurrentTimeStep, true);
		B.ServeAll(CurrentTimeStep, true);
		C.ServeAll(CurrentTimeStep, true);
		D.ServeAll(CurrentTimeStep, true);
		A.MotorBack(CurrentTimeStep);
		B.MotorBack(CurrentTimeStep);
		C.MotorBack(CurrentTimeStep);
		D.MotorBack(CurrentTimeStep);
		

	}
	while (!A.GetEmptyWaitingMotorQueues() || !B.GetEmptyWaitingMotorQueues() || !C.GetEmptyWaitingMotorQueues() || !D.GetEmptyWaitingMotorQueues())
	{
		CurrentTimeStep++;
		A.MotorBack(CurrentTimeStep);
		B.MotorBack(CurrentTimeStep);
		C.MotorBack(CurrentTimeStep);
		D.MotorBack(CurrentTimeStep);
		
	}


	printinOutPutFile();


}

void Restaurant::PrintAtSatusBar(int &CurrentTimeStep)
{
		int FA = A.getFrozenOrdCount();
		int NA = A.getNormOrdCount();
		int VA = A.getVIPOrdCount();
		int FB = B.getFrozenOrdCount();
		int NB = B.getNormOrdCount();
		int VB = B.getVIPOrdCount();
		int FC = C.getFrozenOrdCount();
		int NC = C.getNormOrdCount();
		int VC = C.getVIPOrdCount();
		int FD = D.getFrozenOrdCount();
		int ND = D.getNormOrdCount();
		int VD = D.getVIPOrdCount();

		int MFA = A.getFrozenMotorCount();
		int MFB = B.getFrozenMotorCount();
		int MFC = C.getFrozenMotorCount();
		int MFD = D.getFrozenMotorCount();
		int MVA = A.getFastMotorCount();
		int MVB = B.getFastMotorCount();
		int MVC = C.getFastMotorCount();
		int MVD = D.getFastMotorCount();
		int MNA = A.getNormalMotorCount();
		int MNB = B.getNormalMotorCount();
		int MNC = C.getNormalMotorCount();
		int MND = D.getNormalMotorCount();

		int ANA=A.getAssignedNormOrd();
		int AVA=A.getAssignedVIPOrd();
		int AFA=A.getAssignedFrozOrd();
        int ANB=B.getAssignedNormOrd();
		int AVB=B.getAssignedVIPOrd();
		int AFB=B.getAssignedFrozOrd();	
		int ANC=C.getAssignedNormOrd();
		int AVC=C.getAssignedVIPOrd();
        int AFC=C.getAssignedFrozOrd();
		int AND=D.getAssignedNormOrd();
		int AVD=D.getAssignedVIPOrd();
		int AFD=D.getAssignedFrozOrd();

		string ANA1 = std::to_string(ANA);
	    string AVA1 = std::to_string(AVA);
		string AFA1 = std::to_string(AFA);
		string ANB1 = std::to_string(ANB);
	    string AVB1 = std::to_string(AVB);
		string AFB1 = std::to_string(AFB);
		string ANC1 = std::to_string(ANC);
	    string AVC1 = std::to_string(AVC);
		string AFC1 = std::to_string(AFC);
		string AND1 = std::to_string(AND);
	    string AVD1 = std::to_string(AVD);
		string AFD1 = std::to_string(AFD);

		string FA1 = std::to_string(FA);
		string NA1 = std::to_string(NA);
		string VA1 = std::to_string(VA);
		string FB1 = std::to_string(FB);
		string NB1 = std::to_string(NB);
		string VB1 = std::to_string(VB);
		string FC1 = std::to_string(FC);
		string NC1 = std::to_string(NC);
		string VC1 = std::to_string(VC);
		string FD1 = std::to_string(FD);
		string ND1 = std::to_string(ND);
		string VD1 = std::to_string(VD);



		string FMA1 = std::to_string(MFA);
		string NMA1 = std::to_string(MNA);
		string VMA1 = std::to_string(MVA);
		string FMB1 = std::to_string(MFB);
		string NMB1 = std::to_string(MNB);
		string VMB1 = std::to_string(MVB);
		string FMC1 = std::to_string(MFC);
		string NMC1 = std::to_string(MNC);
		string VMC1 = std::to_string(MVC);
		string FMD1 = std::to_string(MFD);
		string NMD1 = std::to_string(MND);
		string VMD1 = std::to_string(MVD);
		
		
		string b= "The waiting orders : A " + VA1 + " " + FA1 + " " + NA1 + "   " + "B " + VB1 + " " + FB1 + " " + NB1 + "   " + "C " + VC1 + " " + FC1 + " " + NC1 + "   " + "D " + VD1 + " " + FD1 + " " + ND1 ;
        string a="The available motorcycles : A " + VMA1 + " " + FMA1 + " " + NMA1 + "   " + "B " + VMB1 + " " + FMB1 + " " + NMB1  + "   " + "C " + VMC1 + " " + FMC1 + " " + NMC1 + "   " + "D " + VMD1 + " " + FMD1 + " " + NMD1;
		string c="Time Step is " + to_string(CurrentTimeStep);
		string d="Number of served orders until now : A "+AVA1+" "+AFA1+" "+ANA1+ "   " +"B "+AVB1+" "+AFB1+" "+ANB1+  "   "+ "C "+AVC1+" "+AFC1+" "+ANC1+ "   " +"D "+AVD1+" "+AFD1+" "+AND1;
		pGUI->PrintMessage(c,b,a,d,PrevOrders);

		Sleep(1000);
		pGUI->UpdateInterface();

}




	
void Restaurant::printinOutPutFile()
{
	string name;
	if (nameoffile == "input-file-1")
		name = "Output1";
	else if (nameoffile == "input-file-2")
		name = "Output2";
	else if (nameoffile == "input-file-3")
		name = "Output3";
	else if (nameoffile == "input-file-4")
		name = "Output4";
	else if (nameoffile == "input-file-5")
		name = "Output5";
	else if (nameoffile == "input-file-6")
		name = "Output6";
	else
	{
		pGUI->PrintMessage("Please enter output file name", "", "", "", "");
		name = pGUI->GetString();
	}
	int NumC;
	int Num;
	Order*d;
	ofstream o (name+".txt");
	o<<"FT ID AT WT ST";
	o<<endl;
	SetFinalPriQueue();

	while(!FinOrder->isEmpty())
	{
		FinOrder->dequeue(d);
		increaseOrderCount(d);
		o<<d->getFinishTime()<<"  "<<d->GetID()<<"  "<<d->getarrivaltime()<<"  "<<d->getWaitTime()<<"  "<<d->getserveTime()<<endl;
	}
	o<<"Region A:"<<endl;
	A.printOutput(o,ServA,WaitA);
	o<<endl;
	o<<"Region B:"<<endl;
	B.printOutput(o,ServB,WaitB);
	o<<endl;
	o<<"Region C:"<<endl;
	C.printOutput(o,ServC,WaitC);
	o<<endl;
	o<<"Region D:"<<endl;
	D.printOutput(o,ServD,WaitD);
	o<<endl;

	int numFroz=A.getFrozenOrdCount()+B.getFrozenOrdCount()+C.getFrozenOrdCount()+D.getFrozenOrdCount();
	int numNorm=A.getNormOrdCount()+B.getNormOrdCount()+C.getNormOrdCount()+D.getNormOrdCount();
	int numVIP=A.getVIPOrdCount()+B.getVIPOrdCount()+C.getVIPOrdCount()+D.getVIPOrdCount();
	Num=numFroz+numNorm+numVIP;
	int numFrozMotor=A.getFrozenMotorCount()+B.getFrozenMotorCount()+C.getFrozenMotorCount()+D.getFrozenMotorCount();
	int numNormMotor=A.getNormalMotorCount()+B.getNormalMotorCount()+C.getNormalMotorCount()+D.getNormalMotorCount();
	int numFastMotor=A.getFastMotorCount()+B.getFastMotorCount()+C.getFastMotorCount()+D.getFastMotorCount();
	NumC=numNormMotor+numFrozMotor+numFastMotor;

	o<<"Restaurant :"<<endl;
	o<<"Order:"<<Num<<"[Norm:"<<numNorm<<", Froz:"<<numFroz<<", VIP:"<<numVIP<<"]";
	o<<"MotorC:"<<NumC<<"[Norm:"<<numNormMotor<<", Froz:"<<numFrozMotor<<", VIP:"<<numFastMotor<<"]";
	o<<"Avg Wait ="<<(WaitRest*1.0/Num)<<"," "Avg Serv ="<<(ServeRest*1.0/Num);


}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	A.setGUI(pGUI);
	B.setGUI(pGUI);
	C.setGUI(pGUI);
	D.setGUI(pGUI);

	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{


	case MODE_INTR:
		{
			InterActive();
				break;
		}
	case MODE_STEP:
		{
			stepbystep();
		break;
		}

	case MODE_SLNT:
		{
			Silent();
		break;
		}

	case MODE_DEMO:
		break;

	};

	


}




//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}


//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )
		{
		IncrementTimeStep=1;
		//no more events at current time
			return;
		}
		IncrementTimeStep=0;
		pE->Execute(this);
		
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;	
		//deallocate event object from memory
	}
	if(EventsQueue.peekFront(pE)==0)
		IncrementTimeStep=1;
}


Restaurant::~Restaurant()
{
		delete pGUI;
}

void Restaurant::DeletefromDrawingarea()
{
	Order*d1;
	pGUI->Deldraw(d1);
	pGUI->Deldraw(d1);

}



////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
GUI *Restaurant::getpGUI()
{
	return pGUI;
}




void Restaurant::setAutos(int i)
{
	AutoS=i;
}
int Restaurant::getautos()
{
	return AutoS;

}


/// ==> end of DEMO-related function