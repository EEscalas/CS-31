
#include <string>
#include <cctype>
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
	string route;
	getline(cin, route);
	string newRoute;
	int k = 0;
	while (k != route.size())
	{
		if (isalpha(route[k]))
		{
			newRoute += tolower(route[k]);
			k++;
		}
		if (isdigit(route[k]))
		{
			char number = route[k] - '0';
			if (isalpha(route[k - 1]))
			{
				for (int j = (number-1); j > 0; j--)
				{
					newRoute += route[k - 1];
				}
				k++;
			}
			else if (isdigit(route[k - 1]))
			{
				int twoDigitNumber = 10 * (route[k - 1] - '0') + (route[k] - '0');
				for (int j = (twoDigitNumber-1); j > 0; j--)
				{
					newRoute += route[k - 2];
				}
				k++;
			}
		}
	}
	cout << newRoute << endl;
}