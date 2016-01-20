#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <random>
#include <chrono>
#include "Deck.h"
#include "Card.h"

using namespace std;

/*
constructor of the deck. Shuffles a 52 card deck.
*/

Deck::Deck()
{
	initializeAndShuffleDeck();
}

/*
returns cards to deck and shuffles it
*/

void Deck::initializeAndShuffleDeck() //shuffles the deck and restores the size to 52
{
	_deckCards.clear(); //empties the deck
	Card emptyCard = Card(0, 0); //creates emtpy card to add to deck
	_deckCards.resize(52, emptyCard); //sets the size of the deck to 52

	int cardPosition = 0; //counter for card position

	for (int outerCounter = 1; outerCounter < 5; outerCounter++) //the outer counter represents the suit
	{
		for (int innerCounter = 1; innerCounter < 14; innerCounter++) //the inner counter represents the value
		{
			_deckCards.at(cardPosition).setValue(innerCounter); //sets value
			_deckCards.at(cardPosition).setSuit(outerCounter); //sets suit
			cardPosition++; //increases counter
		}
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle(_deckCards.begin(), _deckCards.end(), std::default_random_engine(seed));
}

/*
prints the cards in the deck
*/

void Deck::printDeck()
{
	for (int counter = 0; counter < _deckCards.size(); counter++)
	{
		cout << "Card: \n Suit: " << _deckCards.at(counter).getSuit() << "\n Value: " << _deckCards.at(counter).getValue() << "\n";
	}
}


Deck::~Deck()
{
}
