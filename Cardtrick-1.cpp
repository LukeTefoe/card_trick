/* File: Cardtrick.cpp
 * Programmer: Luke Tefoe
 * Date: 1/14/2023
 * Course: COP 2931
 *
 * Purpose:
 * Write a program that performs a cardtrick. The program will create a
 * random deck of cards, deal them out, pick them up, and determine the
 * secret card.
 *
*/

#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
void BuildDeck(int deck[], const int size);
void PrintDeck(int deck[], const int size);
void PrintCard(int card);
void Deal(int deck[], int play[][3]);
void PickUp(int deck[], int play[][3], int column);
void SecretCard(int deck[]);

int main()
{

	/* declare and initialize variables */
	int column = 0, i = 0;
        int seeDeck = 0;
        int PlayAgain = 0;
		char *p1 = NULL;



	/* Declare a 52 element array of integers to be used as the deck of cards */
	int deck[52] = { 0 };

	/* Declare a 7 by 3 array to receive the cards dealt to play the trick */
	int play[7][3] = { 0 };

	char name[15];



	/* Generate a random seed for the random number generator. */

	srand(time(0));

	/* Openning message.  Ask the player for his/her name */
	cout << "Hello, I am a really tricky computer program and " << endl
		<< "I can even perform a card trick.  Here's how." << endl
		<< "To begin the card trick type in your name: ";
	cin >> name;

	/* Capitalize the first letter of the person's name. */
	p1 = name;

	if (*p1 >= 'a' && *p1 <= 'z')
	{
		*p1 = *p1 - ('a' - 'A');
	}

	cout << endl << "Thank you " << name << endl;

	do
	{
		/* Build the deck */
		BuildDeck(deck, 52);

		/* Ask if the player wants to see the entire deck. If so, print it out. */
		cout << "Ok " << name << ", first things first.  Do you want to see what " << endl
			<< "the deck of cards looks like (1-yes/0-no)? ";
		cin >> seeDeck;

		if (seeDeck == 1)
		{
			PrintDeck(deck, 52);
		}

		cout << endl << "Now we will start with the trick." << endl;

		cout << endl << name << " pick a card and remember it..." << endl;

		/* Begin the card trick loop */
		for (i = 0; i < 3; i++)
		{
			/* Begin the trick by calling the function to deal out the first 21 cards */
			Deal(deck, play);

			/* Include error checking for entering which column */
			do
			{
				/* Ask the player to pick a card and identify the column where the card is */
				cout << endl << "Which column is your card in (0, 1, or 2)?: ";
				cin >> column;
			} while (column < 0 || column > 2);

			/* Pick up the cards, by column, with the selected column second */
			PickUp(deck, play, column);
		}

		/* Display the top ten cards, then reveal the secret card */
		SecretCard(deck);

		/* if the player wants to play again */
		cout << name << ", would you like to play again (1-yes/0-no)? " << endl;;
		cin >> PlayAgain;
	} while (PlayAgain == 1);

	/* Exiting message */
	cout << endl << endl << "Thank you for playing the card trick!" << endl;
}

void BuildDeck(int deck[], const int size)
{
	int used[52] = { 0 };
	int card = 0, i = 0;

	/* Generate cards until the deck is full of integers */
	while (i < size)
	{
		/* generate a random number between 0 and 51 */
		card = rand() % 52;

		/* Check the used array at the position of the card.
		   If 0, add the card and set the used location to 1.  If 1, generate another number */
		if (used[card] == 0)
		{
			used[card] = 1;
			deck[i] = card;
			i++;
		}
	}
	return;
}

void PrintDeck(int deck[], const int size)
{
	int i = 0;

	/* Print out each card in the deck */
	while (i < 52)
	{
		PrintCard(deck[i]);
		cout << "   ";
		i++;
		PrintCard(deck[i]);
		cout << endl;
		i++;
	}

}

void Deal(int deck[], int play[][3])
{
	int row = 0, col = 0, card = 0;



	/* deal cards by passing addresses of cardvalues from
	   the deck array to the play array                   */
	cout << endl;
	cout << "   Column 0           Column 1           Column 2" << endl;
	cout << "======================================================="
		<< endl;
	for (row = 0; row < 7; row++)
	{
		for (col = 0; col < 3; col++)
		{
			play[row][col] = deck[card];
			PrintCard(play[row][col]);
			card++;
		}
		cout << endl;
	}



	return;
}

void PrintCard(int card)
{
	int rank = 0;
	int suit = 0;

	// Determine the rank of the card and print it out i.e. Queen
	rank = card % 13;

	switch (rank)
	{
	case 0:
		cout << " King";
		break;
	case 1:
		cout << "  Ace";
		break;
	case 11:
		cout << " Jack";
		break;
	case 12:
		cout << "Queen";
		break;
	default:
		cout << setw(5) << rank;
	}
	// Determine the suit of the card and print it out i.e. of Clubs
	suit = card / 13;

	switch (suit)
	{
	case 0:
		cout << " of Clubs    ";
		break;
	case 1:
		cout << " of Hearts   ";
		break;
	case 2:
		cout << " of Diamonds ";
		break;
	case 3:
		cout << " of Spades   ";
		break;
	}

	return;
}

void PickUp(int deck[], int play[][3], int column)
{
	int card = 0, row = 0;
	int first = 0, last = 0;

	switch (column)
	{
	case 0:
		first = 1;
		last = 2;
		break;
	case 1:
		first = 0;
		last = 2;
		break;
	case 2:
		first = 0;
		last = 1;
		break;
	}
	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][first];
		card++;
	}
	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][column];
		card++;
	}
	for (row = 0; row < 7; row++)
	{
		deck[card] = play[row][last];
		card++;
	}

	return;
}

void SecretCard(int deck[])
{
	int card = 0;

	cout << endl << "Finding secret card..." << endl;
	for (card = 0; card < 10; card++)
	{
		PrintCard(deck[card]);
		cout << endl;
	}

	cout << endl << "Your secret card is: ";
	PrintCard(deck[card]);
	cout << endl;
	return;
}

