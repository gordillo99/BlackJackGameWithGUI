#pragma once
#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
#include "Card.h"

using namespace std;

class Person
{
public:
	Person();
	int _money;
	int getMoney(){ return _money; }
	void setMoney(int money);
	void emptyHand(vector<Card> &hand);
	int calculateTotalAndPrintHand(vector<Card> &handToPrint, vector<int> &handValues, bool printHand, string name);
	~Person();
};

