#pragma once
#include <list>
#include <string>
#include "Time.h"

using namespace std;

class Passenger
{
private:
	int passportNo, tel;
	list<int> flights;
	string name, surname, nationallity, address;
	bool checkTime2(Time tLeaving, Time tArriving);

public:
	/* --BOOK FLIGHT-- */
	void book();				 // book flight for each customer (Menu Option 6)
	void bookFromQueue(int num); // book flight for the oldest customer in
								 // (call ONLY when a reservation is cancelled)
	void cancel();				 //cancel a reservation (Menu Option 7)

	/* --SHOW PASSENGER'S INFO-- */
	static bool displayPersonInfo(int passport);

	/* --CHECHKER FOR UNIQUE PASSPORT-- */
	static bool uniquePass(int passport);

	/* --GETTERS-- */
	int getPassport() { return this->passportNo; }
	string getName() { return this->name; }
	string getSurname() { return this->surname; }

	/* --Setter-- */
	void setFirstName(string aName) { this->name = aName; }
	void setLastName(string aName) { this->surname = aName; }
	void setPassportNo(int passport) { this->passportNo = passport; }
};

extern list<Passenger> passengerList; // store the passengers