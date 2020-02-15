


template < typename T>
class PriorityQueue{
Node<T>* frontPtr;
int itemCount;
public:
	PriorityQueue()
	{
	frontPtr=nullptr;
	}
	template < typename T>
	bool isEmpty() const 
	{
	if(frontPtr==nullptr)return 0;
	else return 1;
	}
	template < typename T>
	bool enqueue(const T& newEntry,double prio)
	{
	Node<T>*Temp=new Node<T>(newEntry);
	if(Temp==nullptr)return 0;
	Temp->setpri(prio);
	itemCount++;
	if(frontPtr==nullptr)
	{
	frontPtr=Temp;
	return 1;
	}
	if(Temp->getpri()>frontPtr->getpri())
	{
	Temp->setNext(frontPtr);
	frontPtr=Temp;
	return 1;
	}
	Node<T>*New=frontPtr;
	while(New->getNext()!=nullptr&&New->getNext()->getpri()>Temp->getpri())
	{
	New=New->getNext();
	}
	Temp->setNext(New->getNext());
	New->setNext(Temp);
    
	return 1;
	}
template < typename T>
const T * toArray() const
{
	T* bagContents = new T [itemCount]; 
	Node<T>* curPtr = frontPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents[counter] = curPtr->getItem();
		curPtr = curPtr->getNext();
		counter++;
	} // end while
	return bagContents; 
} // end toArray

template < typename T>
bool dequeue(T& frntEntry)
{
if(frontPtr==nullptr)return 0;

else
{itemCount--;
Node<T>*Temp=frontPtr->getNext();
frntEntry=frontPtr->getItem();
delete frontPtr;
frontPtr=Temp;
return 1;
}


} 
template < typename T>
bool peekFront(T& frntEntry)  const
	{
	if(frontPtr==nullptr)return 0;
	else
	{
	frntEntry=frontPtr->getItem();
	return 1;
	}
	}
~PriorityQueue()
	{}

};
