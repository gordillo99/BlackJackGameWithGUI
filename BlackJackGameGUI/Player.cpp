#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include "Player.h"
#include "Card.h"

using namespace std;

void Player::setMoney(int money)
{
	_money = money;
}

void Player::printPlayerMoney()
{
	cout << "Player Money: $" << _money << "\n";
}

int Player::betMoney()
{
	string bet = "";
	int moneyValue = 0;
	bool continueLoop = false;

	do
	{
		continueLoop = false;
		cout << "Enter the amount to bet (Maximum:" << getMoney() << "): $";
		cin >> bet;
		cout << "\n";

		try
		{
			if (!bet.empty())
			{
				moneyValue = stoi(bet);
			}
			else
			{
				throw invalid_argument("null string");
			}
		}
		catch (invalid_argument& a)
		{
			continueLoop = true;
			cout << "Invalid number entered. Please enter a valid number.\n";
		}

		if (moneyValue > _money)
		{
			cout << "Amount of money entered exceeds the current amount of money you have.\n";
			continueLoop = true;
		}
	} while (continueLoop);

	return moneyValue;
}


Player::~Player()
{
}
