#include"Region.h"
#include"cmath"
Region::Region()
{
	FinalOrder=new Queue<Order*>();
	AllOrderServed=false;
	toWaitMotors=false;
	NormalMotorCount=0;
	FastMotorCount=0;
	FrozenMotorCount=0;
	NormalOrderCount=0;
	VIPOrderCount=0;
	FrozenOrderCount=0;
	AssignedVIPOrd=0;
	AssignedFrozOrd=0;
	AssignedNormOrd=0;
	S="";
}
int Region::getAssignedVIPOrd()
{
	return AssignedVIPOrd;
}
int Region::getAssignedFrozOrd()
{
	return AssignedFrozOrd;

}
int Region::getAssignedNormOrd()
{
	return AssignedNormOrd;
}
Region::~Region()
{}
void Region::setGUI(GUI*P)
{
	pGUI=P;

}

Queue<Order*> *Region::getfinalorders()
{
	return FinalOrder;

}

void Region::promoteNormal(int TS)
{
	if(Normal.getPointerto(0)==nullptr)return;
	while(TS-Normal.getPointerto(0)->getItem()->getarrivaltime()==AutoProm)
	{
		promote(Normal.getPointerto(0)->getItem()->GetID(),0);
	    if(Normal.getPointerto(0)==nullptr)return;
	}

}
void Region::IncrementVIPOrders()
{
	VIPOrderCount++;
}
void Region::IncrementFrozenOrders()
{
	FrozenOrderCount++;
}
void Region::IncrementNormalOrders()
{
	NormalOrderCount++;
}
void Region::printOutput(ofstream &ofile,double Sumserve,double SumWait)
{
	int Num,NumC;
	Order*d=nullptr;
	Num=FrozenOrderCount+NormalOrderCount+VIPOrderCount;
	NumC=FrozenMotorCount+NormalMotorCount+FastMotorCount;
	ofile<<"Order:"<<Num<<"[Norm:"<<NormalOrderCount<<", Froz:"<<FrozenOrderCount<<", VIP:"<<VIPOrderCount<<"]";
	ofile<<"MotorC:"<<NumC<<"[Norm:"<<NormalMotorCount<<", Froz:"<<FrozenMotorCount<<", VIP:"<<FastMotorCount<<"]";
	ofile<<"Avg Wait ="<<(SumWait*1.0/Num)<<"," "Avg Serv ="<<(Sumserve*1.0/Num);

}

bool Region::promote(int id,double m)
{

	Node<Order*>*Temp=Normal.getPointerto(0);
	if(Temp==nullptr)return 0;
	if(Normal.getPointerto(0)->getItem()->GetID()==id)
	{
		Temp->getItem()->settotmon(Temp->getItem()->gettotalmoney()+m);
		Temp->getItem()->settype(TYPE_VIP);
		VIPOrderCount++;
		NormalOrderCount--;
		double p=Temp->getItem()->gettotalmoney()/(Temp->getItem()->getarrivaltime()*Temp->getItem()->GetDistance());
		VIP.enqueue(Temp->getItem(),p);
		Normal.remove(Temp->getItem());
			return 1;
	}



bool t=0;
while(Temp->getNext()!=nullptr)
{
if(Temp->getItem()->GetID()==id)
{
	t=1;   break;
}
else 
{
	Temp=Temp->getNext();
}
}
if(t==1)
{
	Temp->getItem()->settotmon(Temp->getItem()->gettotalmoney()+m);
	Temp->getItem()->settype(TYPE_VIP);
	VIPOrderCount++;
	NormalOrderCount--;
	double p=Temp->getItem()->gettotalmoney()/(Temp->getItem()->getarrivaltime()*Temp->getItem()->GetDistance());
	VIP.enqueue(Temp->getItem(),p);
	Normal.remove(Temp->getItem());
	return 1;
}
return 0;


}


bool Region::Cancell(int id)
{

Node<Order*>*Temp=Normal.getPointerto(0);
if(Temp==nullptr)return 0;
if(Normal.getPointerto(0)->getItem()->GetID()==id)
{    
	DeleteOrder(Temp->getItem());
	Normal.remove(Temp->getItem());
    NormalOrderCount--;
    return 1;
}
bool t=0;
while(Temp->getNext()!=nullptr)
{
if(Temp->getItem()->GetID()==id)
{
	t=1;   break;
}
else 
{
	Temp=Temp->getNext();
}
}
if(t==1)
{
	Normal.remove(Temp->getItem());
	NormalOrderCount--;
	DeleteOrder(Temp->getItem());
	return 1;
}
return 0;


}

void Region::setNormalMotor(int I,int speedMotor,STATUS s,REGION R)
{
	Motorcycle* M=new Motorcycle();
	M->setRegion(R);
	M->setspeed(speedMotor);
	M->setstatus(s);
	M->SetMotorType(TYPE_Nrm);
	M->SetID(I);
	NormalMotor.enqueue(M);
}
void Region::addToOrderList()
{
	

}
void Region::setAutoProm(int p)
{
	AutoProm=p;
} 

void Region::setFrozenMotor(int I,int speedMotor,STATUS s,REGION R)
{
	Motorcycle* M=new Motorcycle();
	M->setRegion(R);
	M->setspeed(speedMotor);
	M->setstatus(s);
	M->SetID(I);
	M->SetMotorType(TYPE_Froz);
	FrozenMotor.enqueue(M);
}
void Region::setFastMotor(int I,int speedMotor,STATUS s,REGION R)
{
	Motorcycle* M=new Motorcycle();
	M->setspeed(speedMotor);
	M->setstatus(s);
	M->setRegion(R);
	M->SetMotorType(TYPE_Fast);
	M->SetID(I);
	FastMotor.enqueue(M);

}
bool Region::Serve(ORD_TYPE R)
{ 
	Motorcycle*M;
	Order*d=nullptr;int FT;
	if(R==TYPE_VIP)
	{
		if(!FastMotor.isEmpty())
		{   
			VIP.dequeue(d);
			assigntimes(d,FastMotorSpeed);
			FastMotor.dequeue(M);
			DeleteOrder(d);
			VIPOrderCount--;
			AssignedVIPOrd++;
			FastMotorCount--;
			M->SetOrdType(d->GetType());
			M->SetOrdID(d->GetID());
			M->setTimeback(d->getserveTime()+d->getFinishTime());
			FinalOrder->enqueue(d);
			S=S+"FA"+std::to_string(M->getID())+"(V"+std::to_string(d->GetID())+") ";
			WaitingMotorFast.enqueue(M,-(d->getserveTime()+d->getFinishTime()));
			return 1;
		}
		else if(!NormalMotor.isEmpty())
		{
			VIP.dequeue(d);
			assigntimes(d,NormalMotorSpeed);
			DeleteOrder(d);
			NormalMotorCount--;
			VIPOrderCount--;
			AssignedVIPOrd++;
			NormalMotor.dequeue(M);
			M->setTimeback(d->getserveTime()+d->getFinishTime());
			FinalOrder->enqueue(d);
			M->SetOrdType(d->GetType());
			M->SetOrdID(d->GetID());
			S=S+"N"+std::to_string(M->getID())+"(V"+std::to_string(d->GetID())+") ";
			WaitingMotorNormal.enqueue(M,-(d->getserveTime()+d->getFinishTime()));
			return 1;
		}
		else if(!FrozenMotor.isEmpty())
		{
			VIP.dequeue(d);
			assigntimes(d,FrozenMotorSpeed);
			DeleteOrder(d);
			VIPOrderCount--;
			FrozenMotorCount--;
			AssignedVIPOrd++;
			FrozenMotor.dequeue(M);
			M->setTimeback(d->getserveTime()+d->getFinishTime());
			FinalOrder->enqueue(d);
			M->SetOrdType(d->GetType());
			M->SetOrdID(d->GetID());
			S=S+"F"+std::to_string(M->getID())+"(V"+std::to_string(d->GetID())+") ";
			WaitingMotorFrozen.enqueue(M,-(d->getserveTime()+d->getFinishTime()));
			return 1;
		}
			return 0;
}

	if(R==TYPE_FROZ)
	{
		 if(!FrozenMotor.isEmpty())
		 {		 
			Frozen.dequeue(d);
			DeleteOrder(d);
			assigntimes(d,FrozenMotorSpeed);
			FrozenMotorCount--;
			FrozenOrderCount--;
			AssignedFrozOrd++;
			FrozenMotor.dequeue(M);
			M->setTimeback(d->getserveTime()+d->getFinishTime());
			FinalOrder->enqueue(d);
			M->SetOrdID(d->GetID());
			M->SetOrdType(d->GetType());
			S=S+"F"+std::to_string(M->getID())+"(F"+std::to_string(d->GetID())+") ";
			WaitingMotorFrozen.enqueue(M,-(d->getserveTime()+d->getFinishTime()));
			return 1;
		}
			return 0;
}	   

	if(R==TYPE_NRM)
	{    
		 if(!NormalMotor.isEmpty())
		{
		   d=Normal.getPointerto(0)->getItem();
			Normal.remove(d);
			assigntimes(d,NormalMotorSpeed);
			NormalMotorCount--;
			NormalOrderCount--;
			AssignedNormOrd++;
			DeleteOrder(d);
			NormalMotor.dequeue(M);
			M->setTimeback(d->getserveTime()+d->getFinishTime());
			FinalOrder->enqueue(d);
			M->SetOrdID(d->GetID());
			S=S+"N"+std::to_string(M->getID())+"(N"+std::to_string(d->GetID())+") ";
			M->SetOrdType(d->GetType());
			WaitingMotorNormal.enqueue(M,-(d->getserveTime()+d->getFinishTime()));
			return 1;
		 }
	  else if(!FastMotor.isEmpty())
		{
			d=Normal.getPointerto(0)->getItem();
			Normal.remove(d);
			assigntimes(d,FastMotorSpeed);
			DeleteOrder(d);
			FastMotorCount--;
			NormalOrderCount--;
			AssignedNormOrd++;
			FastMotor.dequeue(M);		
			M->setTimeback(d->getserveTime()+d->getFinishTime());
			FinalOrder->enqueue(d);
			M->SetOrdID(d->GetID());
			M->SetOrdType(d->GetType());
			S=S+"FA"+std::to_string(M->getID())+"(N"+std::to_string(d->GetID())+") ";
			WaitingMotorFast.enqueue(M,-(d->getserveTime()+d->getFinishTime()));
			return 1;
		}
			return 0;
}




}
bool Region::GetAllServed()
{
	return AllOrderServed;
}
void Region::getstring(string&s)
{
	s=S;
	S.clear();
}

bool Region::GetEmptyWaitingMotorQueues()
{
	return toWaitMotors;
}
void Region::MotorBack(int TS)
{
	Motorcycle*d;
	while(WaitingMotorFast.peekFront(d))
		{
			if(d->getTimeback()==TS)
			{
				WaitingMotorFast.dequeue(d);
				FastMotor.enqueue(d);
				FastMotorCount++;
			}
			else 
				break;
		}
	while(WaitingMotorFrozen.peekFront(d))
		{
			if(d->getTimeback()==TS)
			{
				WaitingMotorFrozen.dequeue(d);
				FrozenMotor.enqueue(d);
				FrozenMotorCount++;
			}
			else
				break;
		}
	while(WaitingMotorNormal.peekFront(d))
		{
			if(d->getTimeback()==TS)
			{
				WaitingMotorNormal.dequeue(d);
				NormalMotor.enqueue(d);
				NormalMotorCount++;
			}
			else 
				break;
		}

	if(AllOrderServed&&WaitingMotorFast.isEmpty()&&WaitingMotorFrozen.isEmpty()&&WaitingMotorNormal.isEmpty())
		toWaitMotors=true;

}

void Region::assigntimes(Order*d,int Speed)
{   int ST;
	int FT;
	if(d!=nullptr)
		{
		  d->setWaitTime(TimeStep-d->getarrivaltime());
		  ST=ceil(d->GetDistance()*1.0/Speed);
		  d->setservingtime(ST);
		  FT=d->getserveTime()+d->getWaitTime()+d->getarrivaltime();
		  d->setfinishingtime(FT);
		}

}
void Region::ServeAll(int CurrentTimeStep,bool All)
{
	TimeStep=CurrentTimeStep;
	bool Text=1;
	while(!Frozen.isEmpty()&&Text)
	{
		Text=Serve(TYPE_FROZ);
	}
	Text=1;
	while(Normal.getPointerto(0)!=nullptr&&Text)
	{
		Text=Serve(TYPE_NRM);
	}
	Text=1;
	while(!VIP.isEmpty()&&Text)
	{
		Text=Serve(TYPE_VIP);
	}
	if(All&&Normal.getPointerto(0)==nullptr&&Frozen.isEmpty()&&VIP.isEmpty())
		AllOrderServed=true;
}

void Region::DeleteOrder(Order*d)
{
	
	pGUI->Deldraw(d);


}

void Region::Assign(Order*O)
{
	if(O->GetType()==TYPE_FROZ)
	{
		Frozen.enqueue(O);
	    FrozenOrderCount++;
		pGUI->AddOrderForDrawing(O);
	}

	if(O->GetType()==TYPE_NRM)
	{	
		Normal.Insert(O);
		pGUI->AddOrderForDrawing(O);
		NormalOrderCount++;
	}
	if(O->GetType()==TYPE_VIP)
	{
		VIP.enqueue(O,O->getpri());
		VIPOrderCount++;
		pGUI->AddOrderForDrawing(O);
	}
}


void Region::setFastMotorSpeed(int s)
{
	FastMotorSpeed=s;

}
int Region::getNormOrdCount()
{
	return NormalOrderCount;
}
int Region::getVIPOrdCount()
{
	return VIPOrderCount;

}
int Region::getFrozenOrdCount()
{
	return FrozenOrderCount;
}

void Region::setFrozenMotorSpeed(int s)
{
	FrozenMotorSpeed=s;
} 
void Region::setNormalMotorSpeed(int s)
{
	NormalMotorSpeed=s;
}
int Region::getNormalMotorSpeed()
{
	return NormalMotorSpeed;
}
int Region::getFrozenMotorSpeed()
{
	return FrozenMotorSpeed;
}
int Region::getFastMotorSpeed()
{
	return FastMotorSpeed;

}
int Region::getNormalMotorCount()
{
	return NormalMotorCount;
}
int Region::getFrozenMotorCount()
{
	return FrozenMotorCount;
}
int Region::getFastMotorCount()
{
	return FastMotorCount;
}
void Region::setNormalMotorNum(int c,REGION R)
{
	NormalMotorCount=c;
	for(int i=1;i<=c;i++)
	{
		setNormalMotor(i,c,IDLE,R);
	}
}
void Region::setFastMotorNum(int c,REGION R)
{
	FastMotorCount=c;
	for(int i=NormalMotorCount+FrozenMotorCount+1;i<=c+NormalMotorCount+FrozenMotorCount;i++)
	{
		setFastMotor(i,c,IDLE,R);
	}
}
void Region::setFrozenMotorNum(int c,REGION R)
{
	FrozenMotorCount=c;
	for(int i=NormalMotorCount+1;i<=c+NormalMotorCount;i++)
	{
		setFrozenMotor(i,c,IDLE,R);
	}
}
