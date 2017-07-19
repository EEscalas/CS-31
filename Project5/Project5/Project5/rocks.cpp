#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int MAXWORDS = 9000;			// establish constants for arrays
const int MAXWORDLEN = 6;

int loadWords(char words[][MAXWORDLEN + 1], int maxWords);
int randInt(int min, int max);
int manageOneRound(const char words[][7], int nWords, int wordnum);

int main()
{
	char wordList[MAXWORDS][MAXWORDLEN + 1];

	int nWords = loadWords(wordList, MAXWORDS);
	
	int rounds = 0;
	cout << "How many rounds would you like to play? ";			// input the number of rounds the person would like to play
	cin >> rounds;
	cin.ignore(10000, '\n');
	cout << endl;

	if (rounds <= 0)
	{
		cout << "The number of rounds must be positive." << endl;
		return 0;
	}

	int runningTotal = 0;
	int max = 0;
	int min = 2147483647;

	for (int k = 1; k <= rounds; k++)		// go through the loop until the rounds are over
	{
		cout << "Round " << k << endl;
		int randomRow = randInt(0, nWords-1);
		char secretWord[MAXWORDLEN + 1];
		strcpy(secretWord, wordList[randomRow]);

		cout << "The secret word is " << strlen(secretWord) << " letters long." << endl;

		int roundScore = manageOneRound(wordList, nWords, randomRow);

		if (roundScore == -1)
		{
			cout << "Please double check your wordnum and nwords values, they are either negative or incorrect." << endl;
			return 0;
		}

		if (roundScore == 1)							// make sure you display a different output "try" when you get it in 1 try
			cout << "You got it in 1 try." << endl;
		else
			cout << "You got it in " << roundScore << " tries." << endl;

		cout.setf(ios::fixed);		// make sure the mean values round to the nearest two decimals
		cout.precision(2);
		
		double mean = 0;

		runningTotal += roundScore;			// add the round score to your running total to later calculate the mean

		mean = static_cast<double>(runningTotal) / k;
		

		if (roundScore < min)
			min = roundScore;
		if (roundScore > max)
			max = roundScore;
		
		cout << "Average: " << mean << ", minimum: " << min << ", maximum: " << max << endl;
		if (k < rounds)
			cout << endl;
	}
}

int manageOneRound(const char words[][7], int nWords, int wordnum)
{	
	if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)		// if any of the inputs are wrong, return -1
		return -1;
		
	int tries = 1;

	char guess[10];			// establish a variable for the probe word

	for (int e = 0; e >= 0; e++)
	{
		cout << "Probe word: ";

		cin.getline(guess, 10);		// input the probe word

		int valid = 0;
		
		if (strlen(guess) < 4 || strlen(guess) > 6)		// if the string is the wrong length, output the error message and continue
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			valid = 1;
			continue;
		}
		else if (!islower(guess[0]))				// if the first letter is not lower case, output the error message and continue
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			valid = 1;
			continue;
		}
		else
		{
			int letter = 0;
			while (guess[letter] != '\0')		// if any of the letters are not lower case, output the error message and continue
			{
				if (!islower(guess[letter]))
				{
					cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
					valid = 1;
					e++;
					break;
				}
				letter++;
			}
		}

		int validWord = 0;
		for (int w = 0; w < nWords; w++)		// make sure that the word is a valid word in the word list
		{
			if (words[w][0] == guess[0])
			{
				for (int l = 0; guess[l] != '\0'; l++)
				{
					if ((l == (strlen(guess) - 1)) && (words[w][l] == guess[l]) && strlen(guess) == strlen(words[w]))
					{
						validWord++;
						break;
					}
					else if (words[w][l] == guess[l])
						continue;
					else break;
				}
				if (validWord != 0)
					break;
			}
		}

		if (validWord == 0 && valid == 0)
		{
			cout << "I don't know that word." << endl;
			valid = 1;
			e++;
		}

		if (strlen(words[wordnum]) == strlen(guess))		// if they guessed the word correctly, return tries, if not, continue onto the next guess
		{
			for (int k = 0; guess[k] != '\0'; k++)
			{
				if (guess[k] == words[wordnum][k] && (k == strlen(guess) - 1))
				{
					return tries;
				}
				if (guess[k] == words[wordnum][k])
					continue;
				if (guess[k] != words[wordnum][k])
					break;
			}
		}

		int mask[7] = { 0 };
		int pebbles = 0;
		int rocks = 0;

		for (int a = 0; words[wordnum][a] != '\0'; a++) // go through all chracters of the secret word
		{
			if (words[wordnum][a] == guess[a] && a < strlen(guess))	// count the rocks and mask labeled characters
			{
				mask[a] = 1;
				rocks++;
			}
			else
			{
				int counter = 0;

				for (int b = 0; guess[b] != '\0'; b++) // go through characters of the probe word to find the pebbles
				{
					if (words[wordnum][a] == guess[b] && mask[b] == 0 && words[wordnum][b] != guess[b])
					{
							mask[a] = 1;
							pebbles++;

							if (guess[b] == guess[b + 1])		// account for the same letter in a row
							{
								int counter = 0;
								for (int j = 0; words[wordnum][j] != '\0'; j++)
								{
									if (words[wordnum][j] == guess[b])
										counter++;
									if (counter > 2)
										pebbles++;
								}
								pebbles--;
							}
					}
				}
			}
		}

		if (valid == 0)	// output the number of rocks and pebbles
		{
			cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl;
			tries++;
		}
	}
}