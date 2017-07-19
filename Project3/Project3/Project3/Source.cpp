#include "grid.h"
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
			newRoute += tolower(route[k]);
		if (isdigit(route[k]))
		{
			char number = route[k] - '0';
			if (isalpha(k - 1))
			{
				for (int j = number; j >= 0; j--)
				{
					newRoute += route[k - 1];
				}
			}
			else if (isalpha(k - 2))
			{
				for (int j = number; j >= 0; j--)
				{
					newRoute += route[k - 2];
				}
			}
		}
	}
}