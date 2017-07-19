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
		return 0;
	}
	else
		cout << "Route is well formed!" << endl;
	
	setSize(6, 6);
	setWall(3, 1);
	setWall(2, 2);
	setWall(3, 3);
	setWall(5, 5);
	draw(2, 1, 3, 4);
	
	int stepsyo = 1;

	cout << navigateRoute(2, 1, 3, 4, route, stepsyo) << endl;
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
	else if (row < 0 || column < 0)					// make sure row and column are within the grid 
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
	int mr = sr;			// moving row starts at the row of the start position
	int mc = sc;			// moving column starts at the column of the start position
	int stepsMoved = 0;
	while (k != route.size())
	{
		if (!clearPosition(mr, mc))
		{
			return 3;
			nsteps = stepsMoved;
		}
		int possible_steps = 0;
		if (isalpha(route[k]))
		{
			if (isalpha(route[k + 1]) || k == (route.size() - 1))			// if the next character is a letter or the last character of the route			
			{
				possible_steps = navigateSegment(mr, mc, route[k], 1);
				stepsMoved += possible_steps;		// add the number of steps possible in that direction
				if (route[k] == 'n')									// add the change in position to moving position	
					mr -= possible_steps;			// if north, moving position goes up one row
				else if (route[k] == 's')
					mr += possible_steps;			// if south, moving position goes down one row
				else if (route[k] == 'e')
					mc += possible_steps;			// if east, moving position goes right one column
				else if (route[k] == 'w')
					mc -= possible_steps;			// if west, moving position goes left one column
				k++;
				if (!clearPosition(mr, mc))
				{
					return 3;
					nsteps = stepsMoved;
				}
			}
			else if (isdigit(route[k + 1]))								// if the next character is a number
			{
				int firstDigit = route[k + 1] - '0';					// save the first digit after the letter as 
				if (isdigit(route[k + 2]))								// if the number contains two digit characters
				{
					int secondDigit = route[k + 2] - '0';				// establish the character as an integer
					int twoDigitNumber = (10 * firstDigit) + secondDigit;	// create the two digit number
					possible_steps = navigateSegment(mr, mc, route[k], twoDigitNumber);
					stepsMoved += possible_steps;			// add the number of steps possible in that direction
					if (route[k] == 'n')				// add the change in position to moving position	
						mr -= possible_steps;			// if north, moving position goes up one row
					else if (route[k] == 's')
						mr += possible_steps;			// if south, moving position goes down one row
					else if (route[k] == 'e')
						mc += possible_steps;			// if east, moving position goes right one column
					else if (route[k] == 'w')
						mc -= possible_steps;			// if west, moving position goes left one column
					k += 3;															// have k skip over the letter, and two digits of the number
					if (!clearPosition(mr, mc))
					{
						return 3;
						nsteps = stepsMoved;
					}
				}
				else
				{										// if first digit is the only digit and k+2 is a letter
					possible_steps = navigateSegment(mr, mc, route[k], firstDigit);
					stepsMoved += possible_steps;			// add the number of steps possible in that direction
					if (route[k] == 'n')				// add the change in position to moving position	
						mr -= possible_steps;			// if north, moving position goes up one row
					else if (route[k] == 's')
						mr += possible_steps;			// if south, moving position goes down one row
					else if (route[k] == 'e')
						mc += possible_steps;			// if east, moving position goes right one column
					else if (route[k] == 'w')
						mc -= possible_steps;			// if west, moving position goes left one column
					k += 2;
					if (!clearPosition(mr, mc))
					{
						return 3;
						nsteps = stepsMoved;
					}
				}
			}
		}
	}
	cout << "End Row: " << mr << endl;
	cout << "End Column: " << mc << endl;
	if (mr == er && mc == ec)
	{
		return 0;
		nsteps = stepsMoved;
	}
	else if (mr != er || mc != ec)
	{
		return 1;
		nsteps = stepsMoved;
	}
}



