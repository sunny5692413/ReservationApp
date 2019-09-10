#include "SeatMap.h"
#include <iostream>
#include <string>

using namespace std;

// to calculate occupied seats
int SeatMap::occupied(vector<vector<char>> seatMap)
{
	int count = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (seatMap[i][j] == 'X')
			{
				count++;
			}
		}
	}
	return count;
}

// to check whether all sits are occupied or not
bool SeatMap::allOccupied(vector<vector<char>> seatMap)
{
	int count = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (seatMap[i][j] == 'X')
			{
				count++;
			}
		}
	}
	if (count == 35)
	{
		return true;
	}
	return false;
}

//to display the sits
void SeatMap::display(vector<vector<char>> seatMap)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << seatMap[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

//take user data
string SeatMap::getData()
{
	string p;
	cout << "Enter valid seat no to check(like 1B) or N to cancel: ";
	getline(cin, p);
	return p;
}

//update sit status
void SeatMap::update(vector<vector<char>> seatMap, int row, int col)
{
	cout << "congrats, the seat is valid. Reserved for you\n";
	cout << "updated seat status..........\n";
	seatMap[row][col] = 'X';
}

//checking whether user request for
//his sit no can be processed or not
bool SeatMap::checkAndAssign(vector<vector<char>> seatMap, string s)
{
	//if user input is not in the range 1A to 7D
	if (s[0] > '7' || s[0] < '1' || s[1] > 'D' || s[1] < 'A')
	{
		cout << "invalid seat number\n"; //invalid sit no
		return false;
	}

	int row = -1, col = -1;
	//find the row no of the user sit
	for (int i = 0; i < 7; i++)
	{
		if (seatMap[i][0] == s[0])
		{
			row = i;
		}
	}
	//find the column no of user sit
	for (int j = 0; j < 5; j++)
	{
		if (seatMap[row][j] == s[1])
		{
			col = j;
		}
	}

	//check whether sit is already occupied or not.
	if (col == -1)
	{
		cout << "Seat is already occupied\n";
		return false;
	}
	else
	{
		//if it's a valid sit & not occupied,
		//process the requested & update the sit as occupied
		update(seatMap, row, col);
	}
	return true;
}

string SeatMap::selectSeat(vector<vector<char>> seatMap)
{
	SeatMap::display(seatMap);
	string input;
	bool shouldBeInLoop = true; // used in loops

	do
	{
		input = SeatMap::getData();
		if (input == "N")
		{
			shouldBeInLoop = false;
		}
		else if (!SeatMap::checkAndAssign(seatMap, input))
		{
			shouldBeInLoop = true;
		}
		else
		{
			shouldBeInLoop = false;
		}
	} while (shouldBeInLoop);

	return input;
}