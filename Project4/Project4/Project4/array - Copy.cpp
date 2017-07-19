#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);


int main()
{
	string h[7] = { "bernie", "hillary", "donald", "jeb", "", "carly", "ben" };
	assert(lookup(h, 7, "carly") == 5);
	assert(lookup(h, 7, "donald") == 2);
	assert(lookup(h, 2, "donald") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "bernie", "hillary", "jeb", "carly" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "bernie?" && g[3] == "carly?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jeb?" && g[3] == "hillary?");

	string e[4] = { "donald", "jeb", "", "carly" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "hillary", "hillary", "hillary", "ben", "ben" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "jeb", "donald", "marco" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "marco" && f[2] == "jeb");

	assert(split(h, 7, "carly") == 3);

	string people[5] = { "hillary", "jeb", "rand", "ben", "john" };
	assert(lookup(people, 3, "john") == -1);

	cout << "All tests succeeded" << endl;

	cout << positionOfMax(people, 5) << endl;

	string test[5] = { "Elena", "Lucille", "Escalas", "Edson", "Bestard" };
	
	int i = rotateLeft(test, 5, 0);
	cout << i << endl;

	for (int k = 0; k < 5; k++)
	{
		cout << test[k] << " ";
	}
	cout << endl;

}

int appendToAll(string a[], int n, string value) 
{
	if (n < 0)			// if n is negative, return -1
		return -1;
	else
		for (int j = 0; j < n; j++)		// go through every element and append the value to all the elements
		{
			a[j] += value;
		}
		return n;
}

int lookup(const string a[], int n, string target)
{
	if (n < 0)			// if n is negative, return -1
		return -1;
	int position = 0;	// set initial position equal to zero
	while (position < n)	// while the position is within the number of elements in the array
	{
		if (a[position] == target)	// if the target is equal to the element in this position, return that position
			return position;
		position++;					// if not, continue on to the next element into the array
	}
	return -1;			// if target is not in array, return -1
}

int positionOfMax(const string a[], int n)
{
	if (n < 0)			// if n is negative, return -1
		return -1;
	if (n == 0)			// if the array has no elements, return -1
		return -1;
	int pos = 0;		// start at element zero
	while (pos < n)		// check all elements of the array
	{
		int other = 0;
		while (other < n)	// check all elements of the array in comparison to the element at position pos
		{
			if (a[pos] >= a[other])
			{
				if (other == n - 1)	// if the element at position pos is greater than all other elements, return pos
					return pos;
				else				// if you haven't reached the last element, check if a[pos] is greater than a[other] for the next element
					other++;
			}
			else pos++;			// if there is an element (other) greater than the element at position pos, exit the loop and check the next position
		}
	}
	return pos;
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0)
		return -1;
	if (n == 0)
		return pos;
	if (pos == (n-1))
		return pos;

	string eliminated = a[pos];				// save the position you are eliminating to later stick it at the end

	for (int k = pos; k < (n - 1); k++)		// go through every element after the postition and move it to the left one
	{
		a[k] = a[k + 1];					// make every element at and after pos the next element until you reach the second to last element
	}
	a[n - 1] = eliminated;					// make the last element the eliminated element
	return pos;

}

int countRuns(const string a[], int n)
{
	if (n < 0)
		return -1;
	if (n == 0)
		return 0;
	int runs = 0;
	int j = 0;
	while (j < n)					// go through j until you reach the last element
	{
		if (j == n - 1)				// if j is the last element, add a run and then break
		{
			runs++;
			break;
		}
		if (a[j] != a[j + 1])		// if a[j] is not equal to the next elements
		{
			runs++;					// then it is a unique identitical item, so add it to the list
			j++;					// move onto the next element
		}
		else
			j++;					// if there ARE multiple identical elements in a row, don't count it as a run until you break the string of identical elements
	}
	return runs;
}

int flip(string a[], int n)
{
	if (n < 0)
		return -1;
	string b[1000];
	for (int k = 0; k < n; k++)			// copy all of the elements into a new string
	{
		b[k] = a[k];
	}
	for (int j = 0; j < n; j++)			// move the element to the flipped position
	{
		a[j] = b[(n - 1) - j];
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;
	int pos = 0;
	int smallerSize;
	if (n1 <= n2)			// find out which array a1 or a2 has the fewest number of elements
		smallerSize = n1;
	else
		smallerSize = n2;
	while (pos < smallerSize)
	{
		if (a1[pos] == a2[pos])			// when the positions are equal increase the position, if they are not, return the position
			pos++;
		else
			return pos;	
	}
	return smallerSize;			// if the array goes through the loop without returning the position where they begin to differ, than return the entire size of the smaller array
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;
	if (n2 == 0)
		return 0;
	int startingPosition;
	int k = 0;
	int m = 0;
	while (k < n1)
	{
		if (a1[k] == a2[0])				// check through the elements of a1 until you find the first element of a2
		{
			startingPosition = k;
			for (int j = 0; j < n2; j++)		// check to make sure all of the subsequent elements of a2 are found in a1 contiguously
			{
				if (a1[k+j] != a2[j])
					return -1;
			}
			return startingPosition;
		}
		k++;
	}
	return -1;						// if the first element of a2 is never found, return -1
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 <= 0 || n2 <= 0)
		return -1;
	int k = 0;
	int j = 0;
	while (k < n1)
	{
		j = 0;
		while (j < n2)
		{
			if (a1[k] == a2[j])			// if the element in a1 at k is equal to any of the elements of a2, return k
				return k;
			else j++;
		}
		k++;
	}
	return -1;
}

int split(string a[], int n, string splitter)
{
	if (n < 0)
		return -1;
	if (n == 0)
		return 0;

	int lessThan = 0;

	string b[1000];
	for (int k = 0; k < n; k++)			// copy a[] to a new array
	{
		b[k] = a[k];
	}
	for (int l = 0; l < n; l++)
	{
		if (b[l] < splitter)		// add all the elements less than the splitter to the array
		{
			a[lessThan] = b[l];
			lessThan++;
		}
	}
	if (lessThan == 0)				// if there are no elements less than the splitter, return n
		return n;
	int position = lessThan;
	for (int e = 0; e < n; e++)		// add all the elements equal to the splitter to the next positions in the array
	{
		if (b[e] == splitter)
		{
			a[position] = splitter;
			position++;
		}
	}
	for (int g = 0; g < n; g++)		// add all the elements greater than the splitter to the next positions in the array
	{
		if (b[g] > splitter)
		{
			a[position] = b[g];
			position++;
		}
	}
	return lessThan;			// return the position where the elements that are less than the splitter end
}