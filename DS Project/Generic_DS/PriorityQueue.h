#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class PriorityQueue
{
private :
	
	Node<T>* backPtr;
	Node<T>* frontPtr;
	

public :
	PriorityQueue();	
    bool enqueue( const T& newEntry, int p);
	bool isEmpty() const ;
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
    PriorityQueue(const PriorityQueue<T> & LQ);
	static void PrintQueue(PriorityQueue<T> Q);
	~PriorityQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, int pri)
{

	Node<T>* newNodePtr = new Node<T>(newEntry, pri);
	// Insert the new node
	if (isEmpty())
    {   
        frontPtr = newNodePtr; // The queue is empty
        backPtr=frontPtr;
    }
    else if (frontPtr==backPtr)
    {
		
        if (frontPtr->getPriority()>=pri)
        {
            frontPtr->setNext(newNodePtr);
            backPtr=newNodePtr;
        }
        else
        {
			Node<T>*p=frontPtr;
            newNodePtr->setNext(p);
            frontPtr=newNodePtr;
        }
    }
	else
    {
        Node<T>*p=frontPtr;
        Node<T>*q=p->getNext();
		int flag=0;

        while (flag==0)
        {
            if(q->getPriority()>=pri)
            {
				
                p=p->getNext();
                if (p!=backPtr)
                {
                    q=q->getNext();
                }
                else
                {
				
                    backPtr->setNext(newNodePtr);
                    backPtr=newNodePtr;
					flag=1;
                }
            }
            else 
            {
				if (p->getPriority()<pri)
                {
                    newNodePtr->setNext(p);
					if (p==frontPtr)
					{
						frontPtr=newNodePtr;
					}
                    flag=1;
                }
                else
                { 
                    p->setNext(newNodePtr);
                    newNodePtr->setNext(q);
                    flag=1;
                }
            }

        }
		//delete p;
		//delete q;
    }
	return true;

} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PriorityQueue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    T temp;
	while(dequeue(temp));
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T" 
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/


template <typename T>
T* PriorityQueue<T>::toArray(int &count)
{
	count = 0;

	if(!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while(p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr= new T[count];
	p = frontPtr;
	for(int i=0; i<count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}


/*
Function: Copy constructor
To avoid shallow copy, 
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T> & LQ)
{	
	frontPtr = backPtr = nullptr;
	Node<T>* NodePtr = LQ.frontPtr;	//start at the front node in LQ

	while (NodePtr)
	{   
        //int pr= NodePtr->getPriority();
		enqueue(NodePtr->getItem(), NodePtr->getPriority());	//get data of each node and enqueue it in this queue 
		if (NodePtr!=LQ.backPtr)
		{
			NodePtr = NodePtr->getNext();
		}
		else
		{
			break;
		}
	}	
}

template <typename T>
void PriorityQueue<T>::PrintQueue(PriorityQueue<T> Q) 
{
	T K;
	cout<<"\nQueue contents: ";
	while(Q.dequeue(K))
		cout << K << " ";
	cout<<endl;
}



#endif