//#pragma once
//
//template < typename T>
//class LinkedList
//{
//Node<T>* head;
//public:
//LinkedList()
//{
//head=nullptr;
//}
//template < typename T>
//void Insert(T d)
//{
//Node <T>*temp=new Node<T>();
//temp->setItem(d);
//if(head==nullptr)head=temp;
//else
//{
//temp->setNext(head);
//head=temp;
//}
//}
//template <typename T>
//bool contain(T n)
//{
//Node<T>*temp=head;
//while(true){
//if(temp==0)return 0;
//else 
//{
//if(temp->getItem()==n)return 1;
//temp=temp->getNext();
//}
//}
//}
//~LinkedList(void){}
//template < typename T>
//void remove(T n)
//{
//Node <T>* temp2;
//Node<T>*temp=head;
//while(true)
//{
//if(temp==nullptr)return;
//
//if(temp->getItem()==n)
//{
//temp2=head;
//temp->setItem(temp2->getItem()());
//head=head->getNext();
//delete temp2;
//return;
//}
//else
//{
//temp=temp->getNext();
//}
//}
//}
//template < typename T>
//void clearall()
//{
//Node<T> *temp;
//while(head!=nullptr)
//{
//temp=head;
//head=temp->getNext();
//delete temp;
//}
//
//}
//template < typename T>
//Node<T>*gethead(){return head;}
//
//template < typename T>
//Node<T>* getpointerto(T n,Node<T>*start)
//{ Node<T>*Temp=start;
//while (Temp!=nullptr)
//{
//if(Temp->getItem()==n)return Temp;
//else Temp=Temp->getNext();
//}
//return nullptr;
//}
//
//template < typename T>
//void print()
//{if(head==nullptr)cout<<"Empty Linked List";
//else
//{
//Node<T>*temp=head;
//while(temp!=0)
//{
//cout<<temp->getItem()<<"";
//temp=temp->getNext();
//}
//cout<<endl;	
//}
//}
//};

