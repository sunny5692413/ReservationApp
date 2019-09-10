#pragma once
#include <list>
#include "Passenger.h"

using namespace std;

struct Node //structure for managing each flight's queue
{
	Passenger person;
	Node* next;
};

class Queue
{
private:
	int queueNo;
	Node* rear;
	Node* front;

public:
	/* --CREATE NEW QUEUE-- */
	Queue(int queueId); // queueID is the same as the flight number for each flight

	/* --ADD/REMOVE ELEMENTS-- */
	void enqueue(Passenger p); // add a new passenger
	void dequeue();			   // remove the passenger add last

	static void display(int num);

	Passenger oldest();

	/* --CHECK FOR EMPTY QUEUE-- */
	bool isEmpty(); // returns true if queue is empty

	/* --GETTERS-- */
	int getNo() { return this->queueNo; }
	Node* getFront() { return this->front; }
	Node* getRear() { return this->rear; }

	/* --SETTERS-- */
	void setFront(Node* f)
	{
		if (f == 0)
		{
			this->front = NULL;
		}
		else
		{
			this->front = f;
		}
	}
	void setRear(Node* r)
	{
		this->rear = r;
	}
};

extern list<Queue> qlist; // store the customers in the flights' waiting queues