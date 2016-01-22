#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <ctype.h>
#include "Person.h"
#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include "Dealer.h"
#include "GameEngine.h"

using namespace std;

void GameEngine::setSplit(bool split)
{
	_showSplitOption = split;
}

void GameEngine::setDouble(bool doub)
{
	_showDoubleOption = doub;
}

void GameEngine::setNewCard(bool newCard)
{
	_showNewCardOption = newCard;
}

void GameEngine::setUserInputForMenu(string userInput)
{
	_userInputForMenu = userInput;
}

void GameEngine::setInsurance(bool insurance)
{
	_showInsuranceOption = insurance;
}

void GameEngine::setStand(bool stand)
{
	_showStandOption = stand;
}

void GameEngine::setPlayerBet(int bet)
{
	_playerBet = bet;
}

void GameEngine::printGameHeader()
{
	cout << "------------------------------------------------------------------------------------------------------\n";
	cout << "                                            Starting New Round\n";
	cout << "------------------------------------------------------------------------------------------------------\n";
}

void GameEngine::menuHandlingControl(vector<Card> &deckCards, Player& player, Dealer& dealer, int money)
{
	_userDecidedToSplit = false;
	_userDecidedToStand = false;

	bool firstTurnFlag = true;
	bool keepMainLoopGoing = true;

	bool firstHandBusted = false;
	bool secondHandBusted = false;
	bool dealerHandBusted;
	int playerTotal1;

	do
	{
		dealerHandBusted = false;
		playerTotal1 = player.Person::calculateTotalAndPrintHand(player.getPlayerHand(), player.getPlayerHandValues(), true, "Player");

		if (player.getPlayerHand().at(0).getValue() == player.getPlayerHand().at(1).getValue() && firstTurnFlag && _playerBet * 2 < money)
		{
			setSplit(true);
		}
		else
		{
			setSplit(false);
		}

		if (dealer.getDealerHand().at(0).getValue() == 1 && firstTurnFlag)
		{
			setInsurance(true);
		}
		else
		{
			setInsurance(false);
		}

		if (_playerBet * 2 < money && firstTurnFlag)
		{
			setDouble(true);
		}
		else
		{
			setDouble(false);
		}

		firstTurnFlag = false;

		bool repeatLoopForUserInput = true;

		do
		{
			menuPrintingControl();

			_userInputForMenu = receiveUserMenuInput();

			repeatLoopForUserInput = validateUserMenuInput();
			cout << "\n";

			if (!repeatLoopForUserInput)
			{
				cout << "The option you entered: " << _userInputForMenu << " is invalid. \n\n";
			}

		} while (!repeatLoopForUserInput);

		if (_userInputForMenu.compare("h") == 0 || _userInputForMenu.compare("H") == 0)
		{
			if (!_userDecidedToSplit)
			{
				cout << "Player hits.\n"; 
				hitMethod(deckCards, player.getPlayerHand());
				playerTotal1 = player.Person::calculateTotalAndPrintHand(player.getPlayerHand(), player.getPlayerHandValues(), true, "Player");
			}
			else
			{
				//TODO: add code for hitting with two hands
			}
		}
		else if (_userInputForMenu.compare("s") == 0 || _userInputForMenu.compare("S") == 0)
		{
			cout << "Player stays.\n";
			break;
		}
		else if (_userInputForMenu.compare("d") == 0 || _userInputForMenu.compare("D") == 0)
		{
			cout << "Player hits.\n";
			_playerBet = _playerBet * 2;
			hitMethod(deckCards, player.getPlayerHand());
			playerTotal1 = player.Person::calculateTotalAndPrintHand(player.getPlayerHand(), player.getPlayerHandValues(), true, "Player");
			break;
		}
		else if (_userInputForMenu.compare("p") == 0 || _userInputForMenu.compare("P") == 0)
		{
			splitCards(player.getPlayerHand(), player.getPlayerHand2());
			_userDecidedToSplit = true;
		}
		else if (_userInputForMenu.compare("i") == 0 || _userInputForMenu.compare("I") == 0)
		{
			//TODO: google these rules...
		}

		if (playerTotal1 > 21)
		{
			firstHandBusted = true;

			if (!_userDecidedToSplit)
			{
				break;
			}
			else
			{
				if (firstHandBusted && secondHandBusted)
				{
					break;
				}
			}
		}

		if (_userDecidedToSplit) //check that none of the hands have busted
		{
			if (playerTotal1 > 21)
			{
				secondHandBusted = true;

				if (firstHandBusted && secondHandBusted)
				{
					break;
				}
			}
		}

	} while (keepMainLoopGoing);

	if (playerTotal1 > 21)
	{
		firstHandBusted = true;
	}

	if (_userDecidedToSplit) //check that none of the hands have busted
	{
		if (player.Person::calculateTotalAndPrintHand(player.getPlayerHand2(), player.getPlayerHandValues2(), false, "Player") > 21)
		{
			secondHandBusted = true;
		}
	}

	int dealersTotal = 0;
	bool keepLoopGoing = false;

	do
	{
		if (firstHandBusted)
		{
			cout << "Player's hand is " << playerTotal1 << ". Player has busted.\nPlayer has lost $" << _playerBet << "\n";
			player.setMoney(money - _playerBet);
		}
		else
		{
			//prints dealer's hand and calculates its value
			dealersTotal = dealer.Person::calculateTotalAndPrintHand(dealer.getDealerHand(), dealer.getDealerHandValues(), true, "Dealer");

			if (dealersTotal > 21)
			{
				//indicate that dealer has busted
				cout << "Dealer's hand has busted with a total of " << dealersTotal << "\n";
				dealerHandBusted = true;
				break;
			}
			else if (dealersTotal > 16 && dealersTotal < 22)
			{
				break;
			}
			else if (dealersTotal < 17)
			{
				//dealer hits
				cout << "Dealer hits.\n";
				hitMethod(deckCards, dealer.getDealerHand());
				keepLoopGoing = true;
			}
		}
		
	} while (keepLoopGoing);

	if (!firstHandBusted)
	{
		if (!dealerHandBusted)
		{
			cout << "Dealer's Total: " << dealersTotal << "\nPlayers's Total: " << playerTotal1 << "\n";
			if (dealersTotal > playerTotal1)
			{
				cout << "Dealer has a higher hand. You have lost $" << _playerBet << ".\n";
				player.setMoney(money - _playerBet);
			}
			else if (dealersTotal == playerTotal1)
			{
				cout << "Dealer and Player are tied. No money was lost/earnt.\n";
			}
			else if (playerTotal1 > dealersTotal)
			{
				cout << "Player has a higher hand. You have won $" << _playerBet << ".\n";
				player.setMoney(money + _playerBet);
			}
		}
		else
		{
			cout << "You have won $" << _playerBet << ".\n";
			player.setMoney(money + _playerBet);
		}
	}

	if (player.getMoney() <= 0)
	{
		cout << "\n GAME OVER\n\n You have run out of money. Insert more money to play again.\n";
		exit(0);
	}
}

void GameEngine::hitMethod(vector<Card> &deckCards, vector<Card> &playerHand) //adds one card to player's hand
{
	Card firstPlayerCard = deckCards.at(0);
	deckCards.erase(deckCards.begin());
	playerHand.push_back(firstPlayerCard);
}

void GameEngine::splitCards(vector<Card> &playerHand, vector<Card> &playerHand2) //splits player's hand
{
	Card cardToMove = playerHand.at(0);
	playerHand2.push_back(cardToMove);
	playerHand.erase(playerHand.begin());
}

void GameEngine::menuPrintingControl()
{
	_acceptedLetters.clear();

	if (getNewCard())
	{
		cout << "Hit. (Press ""h"" key)\n";
		_acceptedLetters.push_back("h");
		_acceptedLetters.push_back("H");
	}

	if (getStand())
	{
		cout << "Stand. (Press ""s"" key)\n";
		_acceptedLetters.push_back("s");
		_acceptedLetters.push_back("S");
	}

	if (getDouble())
	{
		cout << "Double down. (Press ""d"" key)\n";
		_acceptedLetters.push_back("d");
		_acceptedLetters.push_back("D");
	}

	if (getSplit())
	{
		cout << "Split cards. (Press ""p"" key)\n";
		_acceptedLetters.push_back("p");
		_acceptedLetters.push_back("P");
	}

	if (getInsurance())
	{
		cout << "Request insurance. (Press ""i"" key)\n";
		_acceptedLetters.push_back("i");
		_acceptedLetters.push_back("I");
	}
}

string GameEngine::receiveUserMenuInput()
{
	string userInput = "";

	cout << "Enter your option: ";
	cin >> userInput;
	cout << "\n";

	return userInput;
}

bool GameEngine::validateUserMenuInput()
{
	vector<string>::iterator it;

	it = find(_acceptedLetters.begin(), _acceptedLetters.end(), _userInputForMenu);

	if (it != _acceptedLetters.end()) //if found in accepted letters
	{
		return true;
	}
	else //if not found in accepted letters
	{
		return false;
	}
}

GameEngine::~GameEngine()
{
}
