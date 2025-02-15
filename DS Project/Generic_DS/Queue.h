#pragma once
#include <iostream>
using namespace std;
#include "Node.h"

/*This code is an updated version from "Data Abstraction & Problem Solving with C++,WALLS AND MIRRORS ,SIXTH EDITION"*/

/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers, 
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

template <typename T>
class Queue
{
private:
    Node<T>* backPtr;
	Node<T>* frontPtr;
	int counter;

public :
	Queue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry); 
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;
	T* toArray(int & count);	//returns array of T (array if items)
	Queue(const Queue<T> & LQ); //copy constructor
	static void PrintQueue(Queue<T> Q);
	int getcounter() const;

	~Queue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
Queue<T>::Queue()
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
bool Queue<T>::isEmpty() const
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
bool Queue<T>::enqueue(const  T& newEntry) 
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	counter++;
	return true ;
} // end enqueue

template <typename T>
int Queue<T>::getcounter() const
{
	return counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Queue<T>:: dequeue(T& frntEntry)  
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
bool Queue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
Queue<T>::~Queue()
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
T* Queue<T>::toArray(int &count)
{
	count = 0;

	if(!frontPtr)
		return nullptr;

	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while(p)
	{
		count++;
		p = p -> getNext();
	}



	T* Arr = new T[count];
	p = frontPtr;
	for(int i=0; i< count ; i++)
	{
		Arr[i] = p -> getItem();
		p = p-> getNext();
	}
	return Arr;
}


template <typename T>
Queue<T>::Queue(const Queue<T> & LQ)
{	
	frontPtr = backPtr = nullptr;
	Node<T>* NodePtr = LQ.frontPtr;	//start at the front node in LQ

	while (NodePtr)
	{   
		enqueue(NodePtr->getItem());	//get data of each node and enqueue it in this queue 
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
void Queue<T>::PrintQueue(Queue<T> Q) 
{
	T K;
	cout<<"\nQueue contents: ";
	while(Q.dequeue(K))
		cout << K << " ";
	cout<<endl;
}
