#pragma once
#include <vector>

using namespace std;

class SeatMap
{
private:
	static void display(vector<vector<char>> seatMap);
	static string getData();
	static bool checkAndAssign(vector<vector<char>> seatMap, string s);
	static void update(vector<vector<char>> seatMap, int row, int col);

public:
	static int occupied(vector<vector<char>> seatMap);
	static bool allOccupied(vector<vector<char>> seatMap);
	static string selectSeat(vector<vector<char>> seatMap);
};
