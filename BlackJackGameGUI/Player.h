#pragma once

#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
#include "Person.h"
#include "Card.h"

using namespace std;

class Player :
	public Person
{

	private:
		vector<Card> _playerHand;
		vector<Card> _playerHand2;
		vector<int> _playerHandValues;
		vector<int> _playerHandValues2;

	public:
		void printPlayerMoney();
		int calculateTotalAndPrintHand(vector<Card> &handToPrint, vector<int> &handValues, bool printHand);
		vector<Card>& getPlayerHand(){ return _playerHand; }
		vector<Card>& getPlayerHand2(){ return _playerHand2; }
		vector<int>& getPlayerHandValues(){ return _playerHandValues; }
		vector<int>& getPlayerHandValues2(){ return _playerHandValues2; }
		int betMoney();
		~Player();
};

