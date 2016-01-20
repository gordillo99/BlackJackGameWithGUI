#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include "Button.hpp"
#include "stdafx.h"
#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include "Dealer.h"
#include "GameEngine.h"

using namespace std;

sf::Font font;

//player stat variables
int playerCurrentBet = 0;
int playerMoneyCounter = 500;

//button declaration
Button enterBetButton(font, { 70.f, 70.f });
Button increaseBetButton(font, { 70.f, 70.f });
Button decreaseBetButton(font, { 70.f, 70.f });

//string declaration
sf::Text playerCurrentBetText(to_string(playerCurrentBet), font);
sf::Text playerCurrentMoneyText("Player's Money: " + to_string(playerMoneyCounter), font);

//flags
bool showBettingGUI = true;

void betAction()
{
	//triggered method
	showBettingGUI = false;
	/*TODO: ADD REST OF THE CODE*/
}

void increaseAction()
{
	//triggered method
	if (playerMoneyCounter - 50 >= 0)
	{
		playerMoneyCounter -= 50;
		playerCurrentBet += 50;
	}
	playerCurrentBetText.setString(to_string(playerCurrentBet));
}

void decreaseAction()
{
	//triggered method
	if (playerCurrentBet - 50 >= 0)
	{
		playerMoneyCounter += 50;
		playerCurrentBet -= 50;
	}
	playerCurrentBetText.setString(to_string(playerCurrentBet));
}

int main()
{

	//setting up game
	unique_ptr<Player> player(new Player());
	player->setMoney(&playerMoneyCounter);
	unique_ptr<Deck> deck(new Deck());
	unique_ptr<Dealer> dealer(new Dealer());
	unique_ptr<GameEngine> gameEngine(new GameEngine());

	//loading font
	font.loadFromFile("whitrabt.ttf");

	playerCurrentBetText.setCharacterSize(30);
	playerCurrentBetText.setStyle(sf::Text::Bold);
	playerCurrentBetText.setColor(sf::Color::White);
	playerCurrentBetText.setPosition(145, 10);

	playerCurrentMoneyText.setCharacterSize(30);
	playerCurrentMoneyText.setStyle(sf::Text::Bold);
	playerCurrentMoneyText.setColor(sf::Color::White);
	playerCurrentMoneyText.setPosition(650, 10);

	//set button string name
	enterBetButton.setString("Bet");
	increaseBetButton.setString("+$50");
	decreaseBetButton.setString("-$50");

	//set button position
	enterBetButton.setPosition(320, 0);
	increaseBetButton.setPosition(250, 0);
	decreaseBetButton.setPosition(0, 0);

	//set button colors
	enterBetButton.setBackgroundColor(sf::Color(59, 134, 134));
	enterBetButton.setTextColor(sf::Color(11, 72, 107));
	enterBetButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	enterBetButton.setOverTextColor(sf::Color(207, 240, 158));
	enterBetButton.setOverOutlineColor(sf::Color(168, 219, 168));

	increaseBetButton.setBackgroundColor(sf::Color(59, 134, 134));
	increaseBetButton.setTextColor(sf::Color(11, 72, 107));
	increaseBetButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	increaseBetButton.setOverTextColor(sf::Color(207, 240, 158));
	increaseBetButton.setOverOutlineColor(sf::Color(168, 219, 168));

	decreaseBetButton.setBackgroundColor(sf::Color(59, 134, 134));
	decreaseBetButton.setTextColor(sf::Color(11, 72, 107));
	decreaseBetButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	decreaseBetButton.setOverTextColor(sf::Color(207, 240, 158));
	decreaseBetButton.setOverOutlineColor(sf::Color(168, 219, 168));

	//set button thickness and color
	enterBetButton.setOutlineThickness(1.f);
	enterBetButton.setOutlineColor(sf::Color(168, 219, 168));

	increaseBetButton.setOutlineThickness(1.f);
	increaseBetButton.setOutlineColor(sf::Color(168, 219, 168));

	decreaseBetButton.setOutlineThickness(1.f);
	decreaseBetButton.setOutlineColor(sf::Color(168, 219, 168));

	//set trigger functions
	enterBetButton.setTriggerFunction(betAction);
	increaseBetButton.setTriggerFunction(increaseAction);
	decreaseBetButton.setTriggerFunction(decreaseAction);

	sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");
	while (window.isOpen())
	{
		//setup event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			enterBetButton.events(event);
			increaseBetButton.events(event);
			decreaseBetButton.events(event);
		}

		//set window as handler of butttons
		enterBetButton.handler(window);
		increaseBetButton.handler(window);
		decreaseBetButton.handler(window);

		//game engine action
		playerCurrentMoneyText.setString("Player's Money: " + to_string(playerMoneyCounter));

		gameEngine->setPlayerBet(playerCurrentBet);

		player->emptyHand(player->getPlayerHand());
		player->emptyHand(player->getPlayerHand2());
		dealer->emptyHand(dealer->getDealerHand());

		dealer->dealCards(deck->getDeckCards(), player->getPlayerHand());

		//ADD NEW CODE TO THIS METHOD
		//dealer->printDealerHandWithHiddenCard();

		//BRING ALL THIS METHOD TO THIS CLASS
		//gameEngine->menuHandlingControl(deck->getDeckCards(), *player, *dealer, player->getMoney());




		window.clear();

		//betting controls
		if (showBettingGUI)
		{
			window.draw(enterBetButton);
			window.draw(increaseBetButton);
			window.draw(decreaseBetButton);
			window.draw(playerCurrentBetText);
		}

		//always shown
		window.draw(playerCurrentMoneyText);

		window.display();
	}
}