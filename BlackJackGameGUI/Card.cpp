#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "Card.h"


using namespace std;

Card::Card(int v, int s)
{
	setValue(v);
	setSuit(s);
}

void Card::printCardValueAndSuit()
{

	string suitName = "";
	string actualValue = "";

	switch (getSuit())
	{
	case 1:
		suitName = "Hearts";
		break;

	case 2:
		suitName = "Diamonds";
		break;

	case 3:
		suitName = "Spades";
		break;

	case 4:
		suitName = "Clubs";
		break;
	default:
		suitName = "Error: Non-Existant Suit";
		break;
	}

	switch (getValue())
	{
	case 1:
		actualValue = "Ace";
		break;

	case 11:
		actualValue = "Jack";
		break;

	case 12:
		actualValue = "Queen";
		break;

	case 13:
		actualValue = "King";
		break;

	default:
		actualValue = to_string(getValue());
		break;
	}

	cout << "Card: " << actualValue << " of " << suitName << "\n";
}

void Card::setValue(int v)
{
	_value = v;
}

void Card::setSuit(int s)
{
	_suit = s;
}


Card::~Card()
{
}
