#include "Menu.h"
#include "Flight.h"

int main()
{
	Flight::createDefaultFlights();
	Menu::displayMenu();
	return 0;
}
