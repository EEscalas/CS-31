
#include <iostream>
 #include <string>
using namespace std;

// Defining variables of various inputs

int main ()
{
	int unitsSent;
		// UnitsSent uses the type "int" because fractions of units cannot be sent
	string title;
		// The title of a movie is a string of letters, not numbers, so it uses the type "string"
	double basePrice;
		// The basePrice may have cents instead of whole dollar amounts, so it uses the type "double"
	string premium;
		// the inputs "y" and "n" are letter characters, so the type "string" is necessary for the "premium" variable

	// input the units sent

	cout << "Units sent: ";
	cin >> unitsSent;

	// tell the error if the number of units sent is negative

	if (unitsSent < 0)
	{
		cout << "---" << endl;
		cout << "The number of units sent must be nonnegative." << endl;
	}
	// only run the rest of the program if the unitsSent is nonnegative
	else
	{
		cin.ignore(10000, '\n');		// this is necessary when dealing with getline() after using cin >> with an int

		// input the movie title

		cout << "Title: ";
		getline(cin, title);

		if (title == "")
		{
			cout << "---" << endl;
			cout << "You must enter a title." << endl;
		}
		// only run the rest of the program if a title is given correctly
		else
		{
			// input base price

			cout << "Base price: ";
			cin >> basePrice;
			
			//round basPrice to two decimal places in order to make it appear as a proper dollar amount
			
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(2);

			cin.ignore(10000, '\n');		// this is necessary when dealing with getline() after using cin >> with a double

			if (basePrice < 0)
			{
				cout << "---" << endl;
				cout << "The base price must be nonnegative." << endl;
			}
			// only run the rest of the program if the basePrice is nonnegative
			else
			{
				// input premium status

				cout << "Premium item? (y/n): ";
				getline(cin, premium);

				if (premium != "y" && premium != "n")
				{
					cout << "---" << endl;
					cout << "You must enter y or n." << endl;
				}
				// only run the rest of the program if "y" or "n" is given as the input of premium
				else
				{
					// calculate the royalties
					// NOTE: the labels "low" "medium" and "high" associated with the variable Royalty refer to the value of unitsSent, not to the actual royalty rate

					double lowRoyalty;

					// calculating the royalties if the units sent are less than or equal to 400

					if (unitsSent <= 400)
					{
						lowRoyalty = unitsSent * (basePrice * 0.09); // this will be a double b/c int * double = double; important to make final answer sufficiently exact
						cout << "---" << endl;
						cout << title << " earned $" << lowRoyalty << " in royalties." << endl;
					}

					// calculating the royalties if the units sent are more than 400, but less than 1200

					double mediumRoyalty;

					if ((unitsSent > 400 && unitsSent < 1200) && (premium == "y"))
					{
						lowRoyalty = 400 * (basePrice * 0.09);
						mediumRoyalty = lowRoyalty + ((unitsSent - 400) * (basePrice * 0.16));
						cout << "---" << endl;
						cout << title << " earned $" << mediumRoyalty << " in royalties." << endl;
					}

					if ((unitsSent > 400 && unitsSent < 1200) && (premium == "n"))
					{
						lowRoyalty = 400 * (basePrice * 0.09);
						mediumRoyalty = lowRoyalty + ((unitsSent - 400) * (basePrice * 0.13));
						cout << "---" << endl;
						cout << title << " earned $" << mediumRoyalty << " in royalties." << endl;
					}
					
					// calculating the royalties if the units sent are less than or equal to 1200

					double highRoyalty;

					if (unitsSent >= 1200 && premium == "y")
					{
						lowRoyalty = 400 * (basePrice * 0.09); // 400 units will have the lowRoyalty unit rate
						mediumRoyalty = lowRoyalty + (800 * (basePrice * 0.16)); // 800 units will have the mediumRoyalty rate
						highRoyalty = mediumRoyalty + ((unitsSent - 1200) * (basePrice * 0.14)); // the leftovers after 1200 units will have the >1200 rate
						cout << "---" << endl;
						cout << title << " earned $" << highRoyalty << " in royalties." << endl;
					}

					if (unitsSent >= 1200 && premium == "n")
					{
						lowRoyalty = 400 * (basePrice * 0.09);
						mediumRoyalty = lowRoyalty + (800 * (basePrice * 0.13));
						highRoyalty = mediumRoyalty + ((unitsSent - 1200) * (basePrice * 0.14));
						cout << "---" << endl;
						cout << title << " earned $" << highRoyalty << " in royalties." << endl;
					}
				}
			}
		}
	}
}



