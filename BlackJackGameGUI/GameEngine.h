#pragma once
#include <iostream>
#include <stdio.h>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include "Dealer.h"

using namespace std;

class GameEngine
{
	private:
		bool _showSplitOption = false;
		bool _showDoubleOption = false;
		bool _showInsuranceOption = false;
		bool _showNewCardOption = true;
		bool _showStandOption = true;

		bool _userDecidedToStand = false;
		bool _userDecidedToSplit = false;

		string _userInputForMenu = "";
		vector<string> _acceptedLetters;

		int _playerBet = 0;


	public:
		void printGameHeader();
		void menuPrintingControl();
		void menuHandlingControl(vector<Card> &deckCards, Player& player, Dealer& dealer, int* money);

		bool validateUserMenuInput();

		bool getSplit(){ return _showSplitOption; }
		bool getDouble(){ return _showDoubleOption; }
		bool getInsurance(){ return _showInsuranceOption; }
		bool getNewCard(){ return _showNewCardOption; }
		bool getStand(){ return _showStandOption; }

		string getUserInputForMenu(){ return _userInputForMenu; }

		void setSplit(bool split);
		void setDouble(bool doub);
		void setInsurance(bool insurance);
		void setNewCard(bool newCard);
		void setStand(bool stand);
		void setPlayerBet(int bet);

		void hitMethod(vector<Card> &deckCards, vector<Card> &playerHand);
		void splitCards(vector<Card> &playerHand, vector<Card> &playerHand2);

		string receiveUserMenuInput();
		~GameEngine();
};

