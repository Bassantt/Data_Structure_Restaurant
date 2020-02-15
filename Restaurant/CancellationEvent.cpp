#include "CancellationEvent.h"
#include "..\restaurant\Rest\Restaurant.h"


CancellationEvent::CancellationEvent(int t,int i):Event(t, i)
{
	id=i;
}

void CancellationEvent::Execute(Restaurant *pRest)
{  
	pRest->A.Cancell(id);
	pRest->B.Cancell(id);
	pRest->C.Cancell(id);
	pRest->D.Cancell(id);

}	//override execute function

CancellationEvent::~CancellationEvent(void)
{
}