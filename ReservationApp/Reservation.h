#pragma once
#include "Flight.h"
#include "Passenger.h"
#include <atomic>

using namespace std;

class Reservation
{
private:
	int id;
	Flight flight;
	Passenger passenger;
	string seat;
public:
	int getId() { return this->id; }
	Passenger getPassenger() { return this->passenger; }
	Flight getFlight() { return this->flight; }
	string getSeat() { return this->seat; }
	static int book();
	static int view();
	static void cancel();
};

extern map<int, Reservation> reservations;

extern atomic<int> atomicId;