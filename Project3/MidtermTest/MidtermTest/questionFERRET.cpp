#include <iostream>
using namespace std;
#include <string>


int main()
{
	string str = "Spaceship";
		for (int k = 0; k != str.size(); k++)
		{
			if (str[k] == 'c')
				cout << "Yellin for da C!" << endl;
		}
	cout << "You failed." << endl;
}