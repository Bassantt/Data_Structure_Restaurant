#pragma once


template < typename T>
class LinkedList
{
int itemCount;
Node<T>* head;
public:
	
Node<T>* getPointerto(int i);
LinkedList()
{
head=nullptr;
}
template < typename T>
void Insert(T d)
{
Node <T>*temp=new Node<T>(d);
temp->setNext(nullptr);
itemCount++;
Node<T>*temp2=head;
if(head==nullptr)
{head=temp;return;}
while(temp2->getNext())
{
temp2=temp2->getNext();
}
temp2->setNext(temp);

}
template <typename T>
bool contain(T n)
{
Node<T>*temp=head;
while(true){
if(temp==0)return 0;
else 
{
if(temp->getItem()==n)return 1;
temp=temp->getNext();
}
}
}
~LinkedList(void){/*clearall();*/}
template < typename T>
void remove(T n)
{
Node <T>* temp2;Node<T>*temp=head;
if(temp==nullptr)return;
if(head->getItem()==n)
{itemCount--;
head=head->getNext();
delete temp;
temp=nullptr;
return;
}
temp=head;
while(temp&&temp->getNext())
{
if(temp->getNext()->getItem()==n)
{itemCount--;
Node<T>*T=temp->getNext();
temp=T->getNext();
delete T;
T=nullptr;
return;
}
else
temp=temp->getNext();

}
}
template < typename T>
void clearall()
{
Node<T> *temp;
while(head!=nullptr)
{
temp=head;
head=temp->getNext();
delete temp;
}

}
template < typename T>
Node<T>*gethead()
{
return head;
}
template < typename T>
 T * toArray() 
{
	T* bagContents = new T [itemCount]; 
	Node<T>* curPtr = head;
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
Node<T>* getpointerto(T n,Node<T>*start)
{ Node<T>*Temp=start;
while (Temp!=nullptr)
{
if(Temp->getItem()==n)return Temp;
else Temp=Temp->getNext();
}
return nullptr;
}

template < typename T>
void print()
{if(head==nullptr)cout<<"Empty Linked List";
else
{
Node<T>*temp=head;
while(temp!=0)
{
cout<<temp->getItem()<<"";
temp=temp->getNext();
}
cout<<endl;	
}
}

template < typename T>
LinkedList(LinkedList& l)
{
	head = nullptr;

	Node<T>*temp = l.gethead();
	if (l.gethead() == nullptr)return;
	while (temp != nullptr)
	{
		Insert(temp->getItem());
		temp = temp->getNext();
	}
}


template < typename T>
void deleten(int n)
{
	Node<T>*temp = head; Node<T>*temp2;
	if (n == 1)
	{
		head = temp->getNext();
		delete temp;
	}
	else
	{
		for (int i = 0; i<n - 2; i++)
			temp = temp->getNext();
		temp2 = temp->getNext();
		temp->setnext(temp2->getNext());
		delete temp2;
	}
}


template < typename T>
LinkedList& operator=(LinkedList&l)
{
	head = nullptr;
	Node<T>*temp = l.gethead();
	if (l.gethead() == nullptr)return *this;
	while (temp != nullptr)
	{
		Insert(temp->getItem());
		temp = temp->getNext();
	}
	return*this;
}


};
template < typename T>

Node<T>* LinkedList<T>::getPointerto(int i)
{
int n=0;
if(head==nullptr)return nullptr;
if(i==0)return head;
Node<T>*temp=head;
while(temp->getNext()!=nullptr)
{
	temp=temp->getNext();
	n++;
	if(n==i)return temp;

}
return nullptr;
}