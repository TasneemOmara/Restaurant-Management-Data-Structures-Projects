#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	               //Pointer to the head of the list
	int count;	                   //Number of nodes in the list
public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}

	//Function: PrintList.
	//prints the values of all nodes in a linked list.
	void PrintList()	const
	{
		cout<<"\nList has "<<count<<" nodes";
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}

	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;

	}

	//Function: DeleteAll.
	//Deletes all nodes of the list.
	void DeleteAll()
	{
		Node<T> *p = Head;
		Node<T>* temp = Head;
		while (p)
		{
			temp = p->getNext();
			delete p;
			p = temp;
		}
		count = 0;
	}

	//InsertEnd
	//inserts a new node at end if the list
	void InsertEnd(const T &data){

		if(Head == nullptr){
			InsertBeg(data);
			return;
		}
		else{
			Node<T> *p = Head;
			while(p->getNext()){
				p = p->getNext();
				}
			Node<T> *R = new Node<T>(data);
			p->setNext(R);
			count++;
			return;

		}

	}

	//Find
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key){
		Node<T> *p = Head;
		while(p){
			if(p->getItem() == Key){
				cout<<"Found the element "<<Key<<endl;
				return true;
			}
			p = p->getNext();
		}
		cout<<"\nElement "<<Key<<" not found"<<endl;
		return false;
	}


	//DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst(){
		cout<<"\nDeleting the first element"<<endl;
		if(Head){
			Node<T> *p = Head->getNext();
			delete Head;
			Head = p;
			count--;
		}
		return;
	}


	//DeleteLast
	//Deletes the last node in the list
	void DeleteLast(){
		cout<<"\nDeleting the last element"<<endl;
		if(Head == nullptr){
			return;
		}
		else if(Head->getNext() == nullptr){
			DeleteFirst();
			return;
		}
		else{
			Node<T> *p = Head;
			Node<T> *q = p->getNext();
			while(q->getNext()){
				p = q;
				q = p->getNext();
			}
			delete q;
			p->setNext(nullptr);
			count--;
			return;

		}
	}

	//DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const int &value){
		cout<<"\nDeleting the element "<<value<<endl;
		if(Head == nullptr){
			return false;
		}

		if(Head->getItem() == value){
			DeleteFirst();
			return true;
		}
		Node<T> *p = Head;
		Node<T> *q = p->getNext();

		while(q){
			if(q->getItem()== value){
				p->setNext(q->getNext());
				delete q;
				count--;
				return true;
			}
			p = q;
			q = p->getNext();
		}
		return false;
	}

	//DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T &value){
		cout<<"\nDeleting all the elements of value "<<value<<endl;
		if(Head == nullptr){return false;}
		bool flag = false;
		while(Head->getItem() == value){
			DeleteFirst();
			flag = true;
		}
		Node<T>* p = Head;
		while(p->getNext()){
			if((p->getNext())->getItem() == value){
				Node<T>* R = (p->getNext())->getNext();
				delete p->getNext();
				p->setNext(R);
				flag= true;
				count--;

			}
			else{
				p = p->getNext();
			}
		}
		return flag;
	}

	//getting head and count 
	Node<T>* getHead() const{
		return Head;
	}

	int getCount(){
		return count;
	}

	void Print_kth_data(int k){
	    if (k<=count)
        {
            Node<T> *p = Head;
            for (int i=1; i<k; i++)
            {
             p = p->getNext();
            }
            cout <<"The data of element number "<< k << "is [ " << p->getItem()<<" ]"<<endl;
        }
        else
            cout<<"Beyond List Length"<<endl;
	}


	T* LinkedList<T>::toArray()
	{

		T* Arr= new T[count];
		Node<T>* p  = Head;
		for(int i=0; i<count;i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}

};

#endif
