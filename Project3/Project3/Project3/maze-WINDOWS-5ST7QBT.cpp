#include "grid.h"
#include <string>
#include <cctype>
#include <cassert>
#include <iostream>
using namespace std;

bool isRouteWellFormed(string route);

int navigateSegment(int r, int c, char dir, int maxSteps);
bool clearPosition(int row, int column);
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps);

int main()
{
	string route;
	getline(cin, route);
	if (!isRouteWellFormed(route))
	{
		cout << "Route is not well formed!" << endl;
	}
	else
		cout << "Route is well formed!" << endl;

	setSize(15, 20);
	setWall(4, 5);
	setWall(3, 8);
	setWall(3, 3);
	setWall(10, 8);
	draw(12, 1, 13, 14);
	
	int stepsyo = 1;
	cout << navigateRoute(1, 1, 2, 2, route, stepsyo) << endl;
	switch (navigateRoute(12, 1, 13, 14, route, stepsyo))
	{
		case 0:
			cout << "valid route. valid start/end points. robot ends at (er, ec). Congrats!" << endl;
			break;
		case 1:
			cout << "valid route. valid start/end points. robot does not end at (er, ec). sorry :(" << endl;
			break;
		case 2:
			cout << "not a valid route or not valid start/end points. #youmessedupyo" << endl;
			break;
		case 3:
			cout << "valid route. valid start/end points. Your path hit a wall or fell of the grid. sorry :(" << endl;
			break;
		default:
			cout << "you did something very long because you aren't even getting a correct digit returned....wooowwwww..." << endl;
	}	
		
	cout << "nsteps: " << stepsyo << endl;
}

bool isRouteWellFormed(string route)
{
	for (int position = 0; position != route.size(); position++)
	{
		if (isdigit(route[0]))
			return false;
		if (isalpha(route[position]))
		{
			char letter = tolower(route[position]); // establish this character to ease following if statement
			if (letter == 'n' || letter == 's' || letter == 'e' || letter == 'w') // if the letter is n, s, e, or w, continue (position++)
				continue;
			else
				return false;
		}
		else if (isdigit(route[position]))
		{
			int digit1 = route[position];		// simplify calculations by adding integer
			int digit2 = position + 1;			// digit 2 indicates the character following the digit
			if (digit1 < 0)						// if the first digit is negative, the string is not correct, therefore return false
				return false;
			else if (isdigit(route[digit2]))	// if the digit is positive, check to see if the next character is a digit
			{
				if (digit2 < 0)					// make sure the next digit is nonnegative
					return false;
				int digit3 = position + 2;		// digit 3 indicates the character two positions away from the first digit
				if (isdigit(route[digit3]))		// if the 3rd character in this sequence is a digit, then the string is not in the proper form
				{
					return false;
				}
				else
					continue;
			}
			else
				continue;
		}
		else if (position != (route.size() - 1)) // if none of the above if statements apply, and we have not reached the end of the string
			return false;						// then there is a character that is not a letter or a digit in the string, making it invalid 
	}
	return true;
}

int navigateSegment(int r, int c, char dir, int maxSteps)
{
	int nSteps = -1;							// start at -1 steps because the first step in the while loop is just the starting position, not motion to a new step
	if (r > getRows() || c > getCols())			// if the point given is outside of the grid, point not valid
		return -1;
	else if (isWall(r, c))						// if the point given is a wall, point not valid
		return -1;
	else
	{
		while (getRows() >= r && getCols() >= c && r > 0 && c > 0) // while the point is within the grid
		{
			if (isWall(r,c))										// if the position is a wall, end the path								
				break;
			else
				nSteps++;											// if the position is not a wall, count it as a step								
			if (tolower(dir) == 'n')								// if dir is north, check the point one row above it
				r--;
			if (tolower(dir) == 's')								// if dir is south, check the point one row below it
				r++;
			if (tolower(dir) == 'e')								// if dir is east, check the point one column to the right
				c++;
			if (tolower(dir) == 'w')								// if dir is east, check the point one column to the left
				c--;
		}
		if (nSteps >= maxSteps)			// if the possible steps are greater than or equal to the max steps, return the maxsteps
			return maxSteps;
		else return nSteps;				// if the possible steps are less than max steps, return the possible steps
	}
}


bool clearPosition(int row, int column)
{
	if (row > getRows() || column > getCols())      
		return false;
	else if (row <= 0 || column <= 0)					// make sure row and column are within the grid 
		return false;								
	else if (isWall(row, column))				    // if it's inside the boundaries, check to see if there is a wall in new location
		return false;								// if there's a wall in the position you want to step to, return false (step not valid)
	else return true;								// if the new step passes these tests, return true because the step is valid
}

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
	if (!isRouteWellFormed || !clearPosition(sr, sc) || !clearPosition(er, ec))
		return 2;
	int k = 0;
	int m = 0;
	int mr = sr;			// moving row starts at the row of the start position
	int mc = sc;			// moving column starts at the column of the start position
	int stepsMoved = 0;
	int possible_steps = 0;
	string newRoute;		// modified route in which every letter 
	while (k != route.size())	// go through every character of the route string
	{
		if (isalpha(route[k]))	// if the character is a letter
		{
			newRoute += tolower(route[k]);	// add the lowercase equivalent of that letter to newRoute
			k++;							// increase k to move onto next character in string
		}
		if (isdigit(route[k]))	// if the character is a digit
		{
			int number = route[k] - '0';	// change the character to a number
			if (isalpha(route[k - 1]))		// if there is a letter before the digit
			{
				for (int j = (number - 1); j > 0; j--)
				{
					newRoute += tolower(route[k - 1]);	// output that letter the digit number of times
				}
				k++;									// increase k to move onto next character in string
			}
			else if (isdigit(route[k - 1]))				// if the character before the digit is another digit
			{
				int twoDigitNumber = (10 * (route[k - 1] - '0')) + (route[k] - '0');		// convert the number to the value of a two digit number
				for (int n = (twoDigitNumber - 1); n > 0; n--)
				{
					newRoute += tolower(route[k - 2]);	// output that letter the digit number of times
				}
				k++;									// increase k to move onto the next character in string
			}
		}
	}
	while (m != newRoute.size())
	{
		possible_steps = navigateSegment(mr, mc, newRoute[m], 1);
		stepsMoved += possible_steps;		// add the number of steps possible in that direction
		if (possible_steps < 1)
		{
			nsteps = stepsMoved;
			return 3;
		}
		if (newRoute[m] == 'n')				// add the change in position to moving position	
			mr -= possible_steps;			// if north, moving position goes up one row
		else if (newRoute[m] == 's')
			mr += possible_steps;			// if south, moving position goes down one row
		else if (newRoute[m] == 'e')
			mc += possible_steps;			// if east, moving position goes right one column
		else if (newRoute[m] == 'w')
			mc -= possible_steps;			// if west, moving position goes left one column
		m++;
	}
	if (mr == er && mc == ec)
	{
		nsteps = stepsMoved;
		return 0;
	}
	else
	{
		nsteps = stepsMoved;
		return 1;
	}
}



