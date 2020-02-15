//
//template < typename T>
//class PriorityQueue
//{
//Node<T>* frontPtr;
//public:
//	PriorityQueue()
//	{
//	frontPtr=nullptr;
//	}	
//	bool isEmpty() const 
//	{
//	if(frontPtr==nullptr)return 0;
//	else return 1;
//	}
//	bool enqueue(const T& newEntry,double prio)
//	{
//	Node<T>*Temp=new Node<T>(newEntry);
//	Temp->setpri(prio);
//	if(Temp==nullptr)return 0;
//	if(frontPtr==nullptr)
//	{
//	frontPtr=Temp;
//	return 1;
//	}
//	if(Temp->getpri()>frontPtr->getpri())
//	{
//	Temp->setNext(frontPtr);
//	frontPtr=Temp;
//	return 1;
//	}
//	Node<T>*New=frontPtr;
//	while(New->getNext()!=nullptr&&New->getNext()->getpri()>Temp->getpri())
//	{
//	New=New->getNext();
//	}
//	Temp->setNext(New->getNext());
//	New->setNext(Temp);
//    
//	return 1;
//	}
//	bool dequeue(T& frntEntry)
//	{
//	if(frontPtr==nullptr)return 0;
//	else
//	{
//	Node<T>*Temp=frontPtr->getNext();
//	frntEntry=frontPtr;
//	delete frontPtr;
//	frontPtr=Temp;
//	return 1;
//	}
//	
//	} 
//	bool peekFront(T& frntEntry)  const
//	{
//	if(frontPtr==nullptr)return 0;
//	else
//	{
//	frntEntry=frontPtr;
//	return 1;
//	}
//	}
//	~PriorityQueue()
//	{}
//
//
//
//};
