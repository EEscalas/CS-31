#include <iostream>
using namespace std;
#include <string>
#include <cctype>

bool isRouteWellFormed(string route);

int main()
{
	string route1;
	getline(cin, route1);
	if (isRouteWellFormed(route1))
		cout << "Route is well formed" << endl;
	else
		cout << "Route is not well formed" << endl;

}

bool isRouteWellFormed(string route)
{
	int ndigits = 0;
	for (int position = 0; position != route.size(); position++)
	{
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
			int digit1 = route[position];		//simplify calculations by adding integer
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
