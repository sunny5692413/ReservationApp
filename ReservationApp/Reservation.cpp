
#include "Reservation.h"
#include "Flight.h"
#include "Helpers.h"
#include "SeatMap.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

map<int, Reservation> reservations;

atomic<int> atomicId;

int Reservation::book()
{
	Reservation reservation;
	bool shouldBeInLoop = true; // used in loops
	string temp;				// stores user's input temp

	// Firstly - show all flights
	Flight::displayAllFlights();

	// Secondly - choose a flight number
	// clean stream
	cin.clear();
	cin.ignore(256, '\n');

	do
	{
		cout << "Flight Number: ";
		getline(cin, temp);
		if (!Helpers::checkNumber(temp))
		{
			cout << "Please enter a valid Flight Number! " << endl;
			shouldBeInLoop = true;
		}
		else if (flights.find(atoi(temp.c_str())) == flights.end())
		{
			cout << "Flight doesn't exist. Please enter a valid Flight Number! " << endl;
			shouldBeInLoop = true;
		}
		else if (SeatMap::allOccupied(flights.at(atoi(temp.c_str())).getSeatMap()))
		{
			cout << "The flight is full! " << endl;
			shouldBeInLoop = true;
		}
		else
		{
			reservation.flight = flights.at(atoi(temp.c_str()));
			shouldBeInLoop = false;
		}
	} while (shouldBeInLoop);

	// Thirdly - collect passenger information
	cout << "Please give us your personal info. " << endl;

	/* --First NAME-- */
	shouldBeInLoop = true;
	temp.clear();
	do
	{
		cout << "First Name: ";
		getline(cin, temp);
		if ((temp.length() <= 10) && (Helpers::checkString(temp)))
		{
			reservation.passenger.setFirstName(temp);
			shouldBeInLoop = false;
		}
		else
		{
			cout << "Please insert a valid Name! ";
		}
	} while (shouldBeInLoop);

	/* --Last NAME-- */
	shouldBeInLoop = true;
	temp.clear();
	do
	{
		cout << "Last Name: ";
		getline(cin, temp);
		if ((temp.length() <= 10) && (Helpers::checkString(temp)))
		{
			reservation.passenger.setLastName(temp);
			shouldBeInLoop = false;
		}
		else
		{
			cout << "Please insert a valid Name! ";
		}
	} while (shouldBeInLoop);

	/* -- Travel Document-- */
	shouldBeInLoop = true;
	temp.clear();
	do
	{
		cout << "Travel Document Number No.: ";
		getline(cin, temp);
		if ((temp.length() <= 10) && (Helpers::checkNumber(temp)))
		{
			reservation.passenger.setPassportNo(atoi(temp.c_str()));
			shouldBeInLoop = false;
		}
		else
		{
			cout << "Please insert a valid Travel Document No.! ";
		}
	} while (shouldBeInLoop);

	// Fourthly - seat selection
	string seat = SeatMap::selectSeat(reservation.flight.getSeatMap());
	if (seat == "N")
	{
		return -1;
	}

	reservation.seat = seat;

	// Fifthly - auto generate reservation id
	reservation.id = ++atomicId;

	// Sixthly - add to reservation map
	pair<int, Reservation> pair;
	pair.first = reservation.id;
	pair.second = reservation;
	reservations.insert(pair);

	cout << "Reservation created! Please keep a record of the ticket number>> " << reservation.id << " <<";
	return reservation.id;
}

int Reservation::view()
{
	if (reservations.empty())
	{
		cout << "No reservation!";
		return -1;
	}

	bool shouldBeInLoop = true; // used in loops
	string temp;				// stores user's input temp

	cin.clear();
	cin.ignore(256, '\n');

	do
	{
		cout << "Please enter a ticket number from a reservation: ";
		getline(cin, temp);
		if (!Helpers::checkNumber(temp))
		{
			cout << "Ticket number is not valid, numeric only!";
			shouldBeInLoop = true;
		}
		else if (reservations.find(atoi(temp.c_str())) == reservations.end())
		{
			cout << "Ticket number doesn't exist!";
			shouldBeInLoop = true;
		}
		else
		{
			shouldBeInLoop = false;
		}
	} while (shouldBeInLoop);

	Reservation reservation = reservations.at(atoi(temp.c_str()));

	string l_time, a_time, fullName; // departure and arrivale time
	stringstream convert;
	stringstream convert2;

	cout << "\nFlight Reservation" << endl
		<< endl;
	cout << left << setw(10) << "Ticket#" << left << setw(10) << "Full Name" << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "Seat#" << endl;

	Passenger passenger = reservation.getPassenger();
	Flight flight = reservation.getFlight();

	convert << std::setw(2) << std::setfill('0') << flight.getLeavingTime().hour;
	convert2 << std::setw(2) << std::setfill('0') << flight.getLeavingTime().min;
	l_time = convert.str() + ":" + convert2.str();

	convert.str(std::string());  // clear stringstream "convert"
	convert2.str(std::string()); // clear stringstream "convert2"

	convert << std::setw(2) << std::setfill('0') << flight.getArrivingTime().hour;
	convert2 << std::setw(2) << std::setfill('0') << flight.getArrivingTime().min;
	a_time = convert.str() + ":" + convert2.str();

	fullName = passenger.getSurname() + "/" + passenger.getName();
	cout << left << setw(10) << reservation.getId() << left << setw(10) << fullName << left << setw(10) << flight.getFlightNo() << left << setw(10) << flight.getDeparture() << left << setw(10) << flight.getDestination() << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << reservation.getSeat() << endl;
	return reservation.getId();
}

void Reservation::cancel()
{
	int id = Reservation::view();
	if (id < 0)
	{
		return;
	}
	string temp; // stores user's input temp
	cout << "Do you want to cancel Ticket# " << id << "? (Y/N)";
	getline(cin, temp);
	if (temp == "Y")
	{
		reservations.erase(id);
		cout << "Ticket# " << id << " canceled!";
	}
	else
	{
		cout << "no ticket is canceled.";
	}
	return;
}