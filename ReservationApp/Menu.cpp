#include <string>
#include <iostream>
#include "Menu.h"
#include "Flight.h"
#include "Passenger.h"
#include "Helpers.h"
#include "Reservation.h"

void Menu::displayMenu()
{
	int selection; // user's menu choice
	string temp;   // temp to store user's input

	do
	{
		cout << "\n-----------------------------------------------";

		cout << "\nSunny's Flight Reservation System\n\n";
		cout << "Main Menu\n";
		cout << "1. View All Flights\n";
		cout << "2. Book a Flight\n";
		cout << "3. View Reservations\n";
		cout << "4. Cancel reservation\n";
		cout << "5. Exit\n\n";

		cout << "-----------------------------------------------" << endl;

		cout << "Enter the number of a menu option: ";
		cin >> temp;

		// check validity of input
		while (!Helpers::checkNumber(temp))
		{
			cout << "Please enter a number!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> temp;
		}
		cout << endl;

		selection = atoi(temp.c_str());
		navigate(selection);

	} while (true);
}

void Menu::navigate(int selection)
{
	Flight f;    // FLight's object
	Passenger p; // class Person's object
	string temp; // temp to store input

	switch (selection)
	{
	case 1:
		Flight::displayAllFlights();
		break;
	case 2:
		Reservation::book();
		break;
	case 3:
		Reservation::view();
		break;
	case 4:
		Reservation::cancel();
		break;
	case 5:
		Menu::exitApp();
		break;
	default:
		cout << "Invalid selection \n";
	}
}

void Menu::select(int selection)
{

	Flight f;    // FLight's object
	Passenger p; // class Person's object
	string temp; // temp to store input

	switch (selection)
	{
	case 1:
		Flight::displayAllFlights();
		break;
	case 2:
		if (!flist.empty())
		{
			cout << "Enter the Flight Number you want to delete: ";
			cin >> temp;
			cout << endl;
			while (!Helpers::checkNumber(temp))
			{
				cout << "Flight Number must be a number!" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> temp;
				cout << endl;
			}
			Flight::deleteFlight(atoi(temp.c_str()));
		}
		else
		{
			cout << "There are no flights to delete" << endl;
		}

		break;
	case 3:
		if (!flist.empty())
		{
			Flight::displaySchedule();
		}
		else
		{
			cout << "There are no scheduled flights!" << endl;
		}
		break;
	case 4:
		if (!flist.empty())
		{
			cout << "Please insert flight's number: ";
			cin >> temp;
			cout << endl;
			while (!Helpers::checkNumber(temp))
			{
				cout << "Flight number must be a number!" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> temp;
				cout << endl;
			}
			Flight::displayFlightInfo(atoi(temp.c_str()));
		}
		else
		{
			cout << "There are no scheduled flights!" << endl;
		}
		break;
	case 5:
		if (!passengerList.empty())
		{
			cout << "Please insert passport number: ";
			cin >> temp;
			while (!Passenger::displayPersonInfo(atoi(temp.c_str())))
			{
				cout << "Wrong passport number!" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> temp;
				cout << endl;
			}
		}
		else
		{
			cout << "There are no registered clients at the moment!" << endl;
		}
		break;
	case 6:
		p.book();
		break;
	case 7:
		p.cancel();
		break;
	case 8:
		Menu::exitApp();
		break;
	default:
		cout << "Invalid selection \n";
	}
}

void Menu::exitApp()
{
	cout << "Thank you for using our system! \n";
	exit(1); // exit
}