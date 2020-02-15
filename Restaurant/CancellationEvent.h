#pragma once
#include "..\restaurant\events\event.h"

class CancellationEvent :
	public Event
{int id;
public:

 virtual void Execute(Restaurant *pRest);	//override execute function
CancellationEvent(int i,int t);
~CancellationEvent(void);
};

