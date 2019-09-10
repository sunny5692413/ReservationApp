#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <queue>
#include <sstream>
#include <iomanip>
#include "Flight.h"
#include "Helpers.h"
#include "SeatMap.h"

list<Flight> flist;

map<int, Flight> flights;

void Flight::createDefaultFlights() {
	Flight f1;
	f1.t_leave.hour = 10;
	f1.t_leave.min = 0;
	f1.t_arrive.hour = 18;
	f1.t_arrive.min = 0;
	f1.flightNo = 123;
	f1.from = "SEA";
	f1.to = "YVR";
	f1.plane_type = "Boeing";
	f1.cost = 500;
	f1.seats = 35;
	f1.booked_seats = 0; // not using this field
	f1.seatMap = initializeSeatMap();
	pair<int, Flight> flightPair1;
	flightPair1.first = f1.getFlightNo();
	flightPair1.second = f1;
	flights.insert(flightPair1);

	Flight f2;
	f2.t_leave.hour = 11;
	f2.t_leave.min = 0;
	f2.t_arrive.hour = 19;
	f2.t_arrive.min = 30;
	f2.flightNo = 456;
	f2.from = "SEA";
	f2.to = "YOW";
	f2.plane_type = "AirBus";
	f2.cost = 600;
	f2.seats = 35;
	f2.booked_seats = 0; // not using this field
	f2.seatMap = initializeSeatMap();
	pair<int, Flight> flightPair2;
	flightPair2.first = f2.getFlightNo();
	flightPair2.second = f2;
	flights.insert(flightPair2);

	Flight f3;
	f3.t_leave.hour = 1;
	f3.t_leave.min = 0;
	f3.t_arrive.hour = 19;
	f3.t_arrive.min = 30;
	f3.flightNo = 789;
	f3.from = "SEA";
	f3.to = "HKG";
	f3.plane_type = "COMAC";
	f3.cost = 900;
	f3.seats = 35;
	f3.booked_seats = 0; // not using this field
	f3.seatMap = initializeSeatMap();
	pair<int, Flight> flightPair3;
	flightPair3.first = f3.getFlightNo();
	flightPair3.second = f3;
	flights.insert(flightPair3);

	cout << "Initialized " << flights.size() << " Flights\n";
}

// every flight has a seat map, we now assume that they are the same 35 seats
vector< vector<char> > Flight::initializeSeatMap()
{
	vector< vector<char> > aSeatMap(7, vector<char>(5));
	for (int i = 0; i < 7; i++) {
		//forst column is row number
		aSeatMap.at(i).at(0) = i + 1 + '0';
		for (int j = 1; j < 5; j++) {
			//to represent sit number A,B,C,D respectively
			aSeatMap.at(i).at(j) = 'A' + j - 1;
		}
	}
	return aSeatMap;
}

void Flight::displayAllFlights()
{
	string l_time, a_time; // departure and arrivale time
	stringstream convert;
	stringstream convert2;

	cout << "\n\t\t\t\t FLIGHT SCHEDULE" << endl
		<< endl;
	cout << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10) << "BOOKED" << endl;

	for (auto i = flights.begin(); i != flights.end(); ++i)
	{
		convert.str(std::string());  // clear stringstream "convert"
		convert2.str(std::string()); // clear stringstream "convert2"
		Flight flight = i->second;

		convert << std::setw(2) << std::setfill('0') << flight.getLeavingTime().hour;
		convert2 << std::setw(2) << std::setfill('0') << flight.getLeavingTime().min;
		l_time = convert.str() + ":" + convert2.str();

		convert.str(std::string());  // clear stringstream "convert"
		convert2.str(std::string()); // clear stringstream "convert2"

		convert << std::setw(2) << std::setfill('0') << flight.getArrivingTime().hour;
		convert2 << std::setw(2) << std::setfill('0') << flight.getArrivingTime().min;
		a_time = convert.str() + ":" + convert2.str();

		int booked = SeatMap::occupied(flight.getSeatMap());

		cout << left << setw(10) << flight.getFlightNo() << left << setw(10) << flight.getDeparture() << left << setw(10) << flight.getDestination() << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << flight.cost << left << setw(10) << flight.plane_type << left << setw(10) << flight.seats << left << setw(10) << booked << endl;
	}

	cout << endl;
	return;
}

void Flight::addFlight()
{
	bool flag = false; // used in loops

	/* --Check for arrival, departure time validity (USED ONLY IN BOARDING & ARRIVING TIME)-- */
	vector<string> fields; // stores, splitted,  user input to be checked
	string temp;           // stores user's input temp
	char* pch;             // stores result of function strtok()
	int hour;              // stores hour
	int min;               // store minutes

	cout << "Add new flights by giving the following attributes: \n";

	// clean stream
	cin.clear();
	cin.ignore(256, '\n');

	/* --FLIGHT NUBMER-- */
	cout << "Flight Number: ";
	// get user's input
	getline(cin, temp);

	do
	{
		flag = true;
		// check input
		if (!Helpers::checkNumber(temp))
		{
			cout << "Please insert a valid Flight Number! " << endl;
			flag = false;
			getline(cin, temp);
		}
		else if (Flight::flightExists(atoi(temp.c_str())))
		{
			cout << "This Flight already exists!" << endl;
			cout << "Please insert a valid Flight Number!" << endl;
			flag = false;
			getline(cin, temp);
		}
		else
		{
			flag = true;
			this->flightNo = atoi(temp.c_str());
		}
	} while (!flag);

	/* --DEPARTURE-- */
	cout << "Departure: ";
	flag = false;

	// check input
	do
	{
		getline(cin, temp);
		if ((temp.length() <= 10) && (Helpers::checkString(temp)))
		{
			this->from = temp;
			flag = true;
		}
		else
		{
			cout << "Please insert a valid Departure city! \n";
		}
	} while (!flag);

	/* --DESTINATION-- */
	cout << "Destination: ";
	flag = false;

	// check input
	do
	{
		getline(cin, temp);
		if ((temp.length() <= 10) && (Helpers::checkString(temp)) && (temp.compare(this->from)))
		{
			this->to = temp;
			flag = true;
		}
		else
		{
			cout << "Please insert a valid Destination city! ";
		}
	} while (!flag);

	/* --DEPARTURE TIME-- */
	cout << "Boarding time (e.g. 19:40): "; //ask from user for the boarding time
	flag = false;

	// check input
	do
	{
		getline(cin, temp);

		if (temp.length() != 5 || !checkTime(temp))
		{
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
		}
		char t_temp[100]; // this is a bad idea but I don't know how to avoid using a const

		strcpy(t_temp, temp.c_str());

		//split string
		pch = strtok(t_temp, ":");

		while (pch != NULL)
		{
			fields.push_back(pch);
			pch = strtok(NULL, ":");
		}

		hour = atoi(fields[0].c_str());
		min = atoi(fields[1].c_str());

		// check time
		if ((hour >= 0 && hour <= 23) && (min >= 0 && min <= 59))
		{
			this->t_leave.hour = hour;
			this->t_leave.min = min;
			flag = true;
		}
		else
		{
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
			fields.clear();
		}

	} while (!flag);

	/* --ARRIVAL TIME-- */
	cout << "Arriving time (e.g. 21:40): ";
	flag = false;
	fields.clear(); // clear fields (because it was used before, at "DEPARTURE TIME")

	// check input
	do
	{
		getline(cin, temp);

		if (temp.length() > 5 || !checkTime(temp))
		{
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
		}

		char t_temp[40]; // this is a bad idea but I don't know how to avoid using a const

		strcpy(t_temp, temp.c_str());

		//split string
		pch = strtok(t_temp, ":");

		while (pch != NULL)
		{
			fields.push_back(pch);
			pch = strtok(NULL, ":");
		}

		hour = atoi(fields[0].c_str());
		min = atoi(fields[1].c_str());

		// check validity of time
		if ((hour >= 0 && hour <= 23) && (min >= 0 && min <= 59))
		{
			this->t_arrive.hour = hour;
			this->t_arrive.min = min;
			flag = true;
		}
		else
		{
			cout << "Please insert a valid arriving time (e.g. 19:40)! ";
			fields.clear();
		}

	} while (!flag);

	/* --TICKET COST-- */
	cout << "Ticket price: ";
	do
	{

		getline(cin, temp);
		flag = true;

		// check input
		if (!Helpers::checkNumber(temp))
		{
			cout << "Please insert a valid ticket price!" << endl;
			flag = false;
		}
		else
		{
			flag = true;
			this->cost = atoi(temp.c_str());
		}
	} while (!flag);

	/* --AIRCRAFT TYPE-- */
	cout << "Aeroplane type: ";
	getline(cin, this->plane_type);
	while (this->plane_type.empty())
	{
		cout << "Please insert a valid Aeroplane type!" << endl;
		getline(cin, this->plane_type);
	}

	/* --No OF SEATS-- */
	cout << "Number of seats: ";
	do
	{

		getline(cin, temp);
		flag = true;

		// check input
		if (!Helpers::checkNumber(temp))
		{
			cout << "Please insert a valid number of seats!" << endl;
			flag = false;
		}
		else
		{
			flag = true;
			this->seats = atoi(temp.c_str());
		}
	} while (!flag);

	/* --No of BOOKED SEATS-- */
	cout << "Number of booked seats: ";
	do
	{

		getline(cin, temp);
		flag = true;

		// check input
		if (!Helpers::checkNumber(temp))
		{
			cout << "Please insert a valid number of booked seats!" << endl;
			flag = false;
		}
		else if (atoi(temp.c_str()) > this->seats)
		{
			cout << "Booked seats must be less than plane's seats!" << endl;
			flag = false;
		}
		else
		{
			flag = true;
			this->booked_seats = atoi(temp.c_str());
		}
	} while (!flag);
	cout << endl;

	flist.push_back(*this); // add object to the flist

	Queue q(this->flightNo); // create new queue for the newly added flight
	qlist.push_back(q);      // add object to the qlist

	cout << "Flight No: " << this->flightNo << " was successfully added!" << endl;
}

bool Flight::checkTime(string time)
{ // check the validity of the time (must be xx:xx, where x = Natural number)

	// enter ONLY if string is NOT empty
	if (!time.empty())
	{
		for (int i = 0; i < time.length(); i++)
		{
			if (i == 2)
			{
				if (time.at(i) != ':')
				{
					return false;
				}
			}
			else if (!(time.at(i) >= '0' && time.at(i) <= '9'))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Flight::deleteFlight(int num)
{
	for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i)
	{
		if (num == i->getNo())
		{

			// enter if waiting queue for the flight is NOT empty
			if (!i->isEmpty())
			{
				// delete object from flist
				for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2)
				{
					if (num == (i2->flightNo))
					{
						i2 = flist.erase(i2);
						i = qlist.erase(i);
						cout << "Flight with number: " << num << " was successfully deleted" << endl;
						return;
					}
				}
			}
			else
			{
				cout << "There are passengers in the queue of the flight with No: " << num << endl;
				cout << "Remove ALL of them from the queue first!" << endl;
				return;
			}
		}
	}
	cout << "This flight number doesn't exist!" << endl;
	return;
}

void Flight::displayFlightInfo(int num)
{
	string l_time, a_time; // departure and arrival time
	stringstream convert;
	stringstream convert2;

	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i)
	{
		if (num == i->flightNo)
		{

			convert.str(std::string());  // clear stringstream "convert"
			convert2.str(std::string()); // clear stringstream "convert2"

			convert << i->t_leave.hour;
			convert2 << i->t_leave.min;
			l_time = convert.str() + ":" + convert2.str();

			convert.str(std::string());  // clear stringstream "convert"
			convert2.str(std::string()); // clear stringstream "convert2"

			convert << i->t_arrive.hour;
			convert2 << i->t_arrive.min;
			a_time = convert.str() + ":" + convert2.str();

			cout << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10) << "BOOKED" << endl;
			cout << left << setw(10) << i->flightNo << left << setw(10) << i->from << left << setw(10) << i->to << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << i->cost << left << setw(10) << i->plane_type << left << setw(10) << i->seats << left << setw(10) << i->booked_seats << endl;

			Queue::display(num);
			return;
		}
	}

	cout << "Invalid number of flight was given." << endl;
}

void Flight::displaySchedule()
{
	string l_time, a_time; // departure and arrivale time
	stringstream convert;
	stringstream convert2;

	cout << "\n\t\t\t\t FLIGHT SCHEDULE" << endl
		<< endl;
	cout << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10) << "BOOKED" << endl;

	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i)
	{
		convert.str(std::string());  // clear stringstream "convert"
		convert2.str(std::string()); // clear stringstream "convert2"

		convert << i->t_leave.hour;
		convert2 << i->t_leave.min;
		l_time = convert.str() + ":" + convert2.str();

		convert.str(std::string());  // clear stringstream "convert"
		convert2.str(std::string()); // clear stringstream "convert2"

		convert << i->t_arrive.hour;
		convert2 << i->t_arrive.min;
		a_time = convert.str() + ":" + convert2.str();

		cout << left << setw(10) << i->flightNo << left << setw(10) << i->from << left << setw(10) << i->to << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << i->cost << left << setw(10) << i->plane_type << left << setw(10) << i->seats << left << setw(10) << i->booked_seats << endl;
	}

	cout << endl;
}

void Flight::resSeat(int num, int val)
{
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i)
	{
		if (num == (i->flightNo))
		{
			i->booked_seats += val;
			break;
		}
	}
}

bool Flight::flightExists(int num)
{
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i)
	{
		if (num == i->flightNo)
		{
			return true;
		}
	}
	return false;
}

bool Flight::checkForSeats(int num)
{
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i)
	{
		if (num == (i->flightNo))
		{
			if (i->seats == i->booked_seats)
				return false;
			else
				return true;
		}
	}
}