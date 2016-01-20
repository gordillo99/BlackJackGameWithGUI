// BlackJackGame_V0.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include "Dealer.h"
#include "GameEngine.h"

using namespace std;

void printGameHeader(); //prototype for the function

int _tmain(int argc, _TCHAR* argv[])
{

	unique_ptr<Player> player(new Player());
	//player->setMoney(500);
	unique_ptr<Deck> deck(new Deck());
	unique_ptr<Dealer> dealer(new Dealer());
	unique_ptr<GameEngine> gameEngine(new GameEngine());

	for (;;){


		gameEngine->setPlayerBet(player->betMoney());

		player->emptyHand(player->getPlayerHand());
		player->emptyHand(player->getPlayerHand2());
		dealer->emptyHand(dealer->getDealerHand());

		dealer->dealCards(deck->getDeckCards(), player->getPlayerHand());

		dealer->printDealerHandWithHiddenCard();
	
		gameEngine->menuHandlingControl(deck->getDeckCards(), *player, *dealer, player->getMoney());
	};
	return 0;
}

