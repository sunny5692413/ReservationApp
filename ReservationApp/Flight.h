#pragma once
#include <string>
#include <list>
#include <map>
#include <vector>
#include "Time.h"
#include "Queue.h"

using namespace std;

class Flight
{
private:
	int flightNo, cost, seats, booked_seats;
	string from, to, plane_type;
	Time t_leave, t_arrive;
	bool checkTime(string time);
	vector< vector<char> > seatMap;
	static vector< vector<char> > initializeSeatMap();
public:
	static void createDefaultFlights();

	/* --ADD/REMOVE FLIGHTS--*/
	void addFlight();
	static void deleteFlight(int num);

	/* --DISPLAY FLIGHTS--*/
	static void displayFlightInfo(int num);
	static void displaySchedule();
	static void displayAllFlights();

	/* --BOOK SEATS--*/
	static void resSeat(int num, int val);

	/* --FLIGHT CHECKERS--*/
	static bool flightExists(int num);  // check flight is booked
	static bool checkForSeats(int num); // checks for already registerd flight in the system

	/* --GETTERS--*/
	int getFlightNo() { return this->flightNo; }
	Time getLeavingTime() { return this->t_leave; }
	Time getArrivingTime() { return this->t_arrive; }
	string getDeparture() { return this->from; }
	string getDestination() { return this->to; }
	vector< vector<char> > getSeatMap() { return this->seatMap; }
};

extern list<Flight> flist; // store the flights of the system

extern map<int, Flight> flights; // store all default fights of the system