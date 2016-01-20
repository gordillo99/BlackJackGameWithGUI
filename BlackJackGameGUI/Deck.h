#pragma once

#include <iostream>
#include <stdio.h>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Card.h"

using namespace std;

class Deck
{
private:
	vector<Card> _deckCards;

public:
	int myRandom() { return rand() % 100; }
	void initializeAndShuffleDeck();
	void printDeck();
	Deck();
	vector<Card>& getDeckCards(){ return _deckCards; }
	~Deck();
};

