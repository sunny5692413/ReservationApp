#pragma once

class Menu //class for managing the app's menu
{
public:
	static void displayMenu();         // displays the menu
	static void select(int selection); // receives user's input and performs the corresponding function
	static void navigate(int selection);
	static void exitApp();           // exits the app
};