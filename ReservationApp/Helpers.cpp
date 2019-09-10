#include "Helpers.h"
#include <cctype>
#include <algorithm>

bool Helpers::checkString(string s)
{ // checks if string consists only of letters

	if (!s.empty())
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (!((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')))
			{
				return false;
			}
		}
		return true;
	}
	else
	{ //return false
		return false;
	}
}

bool Helpers::checkNumber(string s)
{ // checks if the input string consists ONLY of numbers

	// enter if string is NOT empty
	if (!s.empty())
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')))
			{
				return false;
			}
		}

		// check if string is a postive number
		if (atoi(s.c_str()) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}