#include "stdafx.h"
#include "Person.h"


#include <algorithm> 
#include <iostream>
#include <string>
#include <stdio.h>
#include "Card.h"

using namespace std;

Person::Person(){}
Person::~Person(){}

void Person::emptyHand(vector<Card> &hand)
{
	hand.clear();
}


int Person::calculateTotalAndPrintHand(vector<Card> &handToPrint, vector<int> &handValues, bool printHand, string name)
{
	handValues.clear();

	if (printHand)
	{
		cout << "\n"<< name <<"'s Hand\n\n";
	}

	int total = 0;

	for (vector<Card>::iterator it = handToPrint.begin(); it != handToPrint.end(); ++it)
	{
		Card c = *it;
		if (printHand){
			c.printCardValueAndSuit();
		}

		if (c.getValue() > 1 && c.getValue() < 11)
		{
			handValues.push_back(c.getValue());
		}
		else if (c.getValue() > 10 && c.getValue() < 14)
		{
			handValues.push_back(10);
		}
		else if (c.getValue() == 1)
		{
			handValues.push_back(11);
		}
	}

	sort(begin(handValues), end(handValues));

	for (vector<int>::iterator it = handValues.begin(); it != handValues.end(); ++it)
	{
		total += *it;
	}

	for (vector<int>::iterator it = handValues.begin(); it != handValues.end(); ++it)
	{
		if (total > 21)
		{
			if (*it == 11)
			{
				*it = 1;
				total -= 10;
			}
		}
		else
		{
			break;
		}
	}


	/*
	if (total > 21) //if the aces being 11 exceeds 21
	{
		bool continueChangingAceValues = false;

		do
		{
			for (vector<int>::iterator it = handValues.begin(); it != handValues.end(); ++it)
			{
				if (*it == 11)
				{
					it = handValues.erase(it);
					it = handValues.insert(it, 1);

					total = 0;

					for (vector<int>::iterator ite = handValues.begin(); ite != handValues.end(); ++ite)
					{
						total += *ite;
					}

					if (total < 21)
					{
						continueChangingAceValues = false;
						break;
					}
				}
			}
		} while (continueChangingAceValues);
	}
	*/
	if (printHand)
	{
		cout << "\n";
		cout << "Total: " << total << "\n\n";
	}

	return total;
}
