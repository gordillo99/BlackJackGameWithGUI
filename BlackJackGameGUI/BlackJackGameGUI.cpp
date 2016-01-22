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

void menuHandlingControl(GameEngine ge, vector<Card> &deckCards, Player& player, Dealer& dealer, int money); //prototype

const int CARD_SPRITE_WIDTH = 73;
const int CARD_SPRITE_HEIGHT = 98;

//Vital variable for game flow and loop control 
int gameStage = 0;

/*
	Stage 0 = user place bets
	Stage 1 = cards are dealt
	Stage 3 = user selects to hit/stay/insure/split (go to 4)
	Stage 4 = cards are dealt (go to 3 as long as necessary)
	Stage 5 = Dealer Plays
	Stage 6 = Game Ends
*/

sf::Font font;

//player stat variables
int playerCurrentBet = 0;
int playerMoneyCounter = 500;

//button declaration
Button enterBetButton(font, { 70.f, 70.f });
Button increaseBetButton(font, { 70.f, 70.f });
Button decreaseBetButton(font, { 70.f, 70.f });
Button hitButton(font, { 70.f, 70.f });
Button stayButton(font, { 70.f, 70.f });
Button splitButton(font, { 110.f, 70.f });
Button insuranceButton(font, { 160.f, 70.f });
Button doubleDownButton(font, { 200.f, 70.f });

//string declaration
sf::Text playerCurrentBetText(to_string(playerCurrentBet), font);
sf::Text playerCurrentMoneyText("Player's Money: " + to_string(playerMoneyCounter), font);
sf::Text dealerHandText("Dealer's Hand", font);

//flags
bool showBettingGUI = true; //Shows the bet and increase/decrease bet buttons
bool showUserButtons = false;

void betAction()
{
	if (playerCurrentBet == 0)
	{
		return;
	}

	//triggered method
	showBettingGUI = false;
	showUserButtons = true;
	gameStage++; //move to stage 1
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

void hitAction()
{

}

void splitAction()
{

}

void stayAction()
{

}

void insuranceAction()
{

}

void doubleDownAction()
{

}

vector<sf::Sprite> createCardSprites(vector<Card> givenCards, int type)
{
	vector<sf::Sprite> createdSprites;
	float firstXPositionOfCards = 0;
	float firstYPositionOfCards = 0;

	switch (type)
	{
		case 0:
		{ //dealer with hidden card
			firstXPositionOfCards = 380;
			firstYPositionOfCards = 200;
			sf::Texture* backCardTexture = new sf::Texture();
			backCardTexture->loadFromFile("BackCardSprite.png");
			sf::Sprite* backCard = new sf::Sprite(*backCardTexture);
			backCard->setTextureRect(sf::IntRect(0, 0, CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT));
			backCard->setPosition(firstXPositionOfCards, firstYPositionOfCards);
			createdSprites.push_back(*backCard);
			firstXPositionOfCards = 300;
		}
			break;

		case 1: //player
		{
			firstXPositionOfCards = 300;
			firstYPositionOfCards = 400;
		}
			break;
		case 2: //dealer final play
		{
			firstXPositionOfCards = 460;
			firstYPositionOfCards = 200;
		}
			break;
	}

	for (vector<Card>::iterator it = givenCards.begin(); it != givenCards.end(); ++it)
	{
		if (type != 0)
		{
			firstXPositionOfCards += 80;
		}
		Card currentCard = *it;
		sf::Texture* newTexture = new sf::Texture();
		newTexture->loadFromFile("CardsSprite.png");
		sf::Sprite* newCard = new sf::Sprite(*newTexture);
		newCard->setTextureRect(sf::IntRect(currentCard.getSuit() * CARD_SPRITE_WIDTH, currentCard.getValue() * CARD_SPRITE_HEIGHT, CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT));
		newCard->setPosition(firstXPositionOfCards, firstYPositionOfCards);
		createdSprites.push_back(*newCard);
	}

	return createdSprites;
}

int main()
{
	//setting up game
	unique_ptr<Player> player(new Player());
	player->setMoney(playerMoneyCounter);
	unique_ptr<Deck> deck(new Deck());
	unique_ptr<Dealer> dealer(new Dealer());
	unique_ptr<GameEngine> gameEngine(new GameEngine());

	vector<sf::Sprite> cardsToRender; 

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
	hitButton.setString("Hit");
	stayButton.setString("Stay");
	splitButton.setString("Split");
	insuranceButton.setString("Insurance");
	doubleDownButton.setString("Double Down");

	//set button position
	enterBetButton.setPosition(320, 0);
	increaseBetButton.setPosition(250, 0);
	decreaseBetButton.setPosition(0, 0);
	hitButton.setPosition(350,700);
	stayButton.setPosition(420,700);
	splitButton.setPosition(490,700);
	insuranceButton.setPosition(600,700);
	doubleDownButton.setPosition(760, 700);

	//set button colors
	enterBetButton.setBackgroundColor(sf::Color(59, 134, 134));
	enterBetButton.setTextColor(sf::Color(11, 72, 107));
	enterBetButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	enterBetButton.setOverTextColor(sf::Color(207, 240, 158));
	enterBetButton.setOverOutlineColor(sf::Color(168, 219, 168));

	hitButton.setBackgroundColor(sf::Color(59, 134, 134));
	hitButton.setTextColor(sf::Color(11, 72, 107));
	hitButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	hitButton.setOverTextColor(sf::Color(207, 240, 158));
	hitButton.setOverOutlineColor(sf::Color(168, 219, 168));

	stayButton.setBackgroundColor(sf::Color(59, 134, 134));
	stayButton.setTextColor(sf::Color(11, 72, 107));
	stayButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	stayButton.setOverTextColor(sf::Color(207, 240, 158));
	stayButton.setOverOutlineColor(sf::Color(168, 219, 168));

	splitButton.setBackgroundColor(sf::Color(59, 134, 134));
	splitButton.setTextColor(sf::Color(11, 72, 107));
	splitButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	splitButton.setOverTextColor(sf::Color(207, 240, 158));
	splitButton.setOverOutlineColor(sf::Color(168, 219, 168));

	insuranceButton.setBackgroundColor(sf::Color(59, 134, 134));
	insuranceButton.setTextColor(sf::Color(11, 72, 107));
	insuranceButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	insuranceButton.setOverTextColor(sf::Color(207, 240, 158));
	insuranceButton.setOverOutlineColor(sf::Color(168, 219, 168));	

	doubleDownButton.setBackgroundColor(sf::Color(59, 134, 134));
	doubleDownButton.setTextColor(sf::Color(11, 72, 107));
	doubleDownButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	doubleDownButton.setOverTextColor(sf::Color(207, 240, 158));
	doubleDownButton.setOverOutlineColor(sf::Color(168, 219, 168));

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

	hitButton.setOutlineThickness(1.f);
	hitButton.setOutlineColor(sf::Color(168, 219, 168));

	stayButton.setOutlineThickness(1.f);
	stayButton.setOutlineColor(sf::Color(168, 219, 168));

	splitButton.setOutlineThickness(1.f);
	splitButton.setOutlineColor(sf::Color(168, 219, 168));

	doubleDownButton.setOutlineThickness(1.f);
	doubleDownButton.setOutlineColor(sf::Color(168, 219, 168));

	insuranceButton.setOutlineThickness(1.f);
	insuranceButton.setOutlineColor(sf::Color(168, 219, 168));

	//set trigger functions
	enterBetButton.setTriggerFunction(betAction);
	increaseBetButton.setTriggerFunction(increaseAction);
	decreaseBetButton.setTriggerFunction(decreaseAction);
	hitButton.setTriggerFunction(hitAction);
	stayButton.setTriggerFunction(stayAction);
	splitButton.setTriggerFunction(splitAction);
	insuranceButton.setTriggerFunction(insuranceAction);
	doubleDownButton.setTriggerFunction(doubleDownAction);

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
		hitButton.handler(window);
		splitButton.handler(window);
		stayButton.handler(window);
		insuranceButton.handler(window);
		doubleDownButton.handler(window);
		
		playerCurrentMoneyText.setString("Player's Money: " + to_string(playerMoneyCounter));

		//game engine action
		if (gameStage == 1)
		{
			gameStage++;
			gameEngine->setPlayerBet(playerCurrentBet);

			player->emptyHand(player->getPlayerHand());
			player->emptyHand(player->getPlayerHand2());
			dealer->emptyHand(dealer->getDealerHand());

			dealer->dealCards(deck->getDeckCards(), player->getPlayerHand());

			//ADD NEW CODE TO THIS METHOD
			vector<sf::Sprite> dealerSprites = createCardSprites(dealer->printDealerHandWithHiddenCard(), 0);
			cardsToRender.insert(cardsToRender.end(), dealerSprites.begin(), dealerSprites.end());
		}
		
		/*
		//GAME HANDLING LOOP STARTS
		GameEngine ge = *gameEngine;
		vector<Card> deckCards = deck->getDeckCards();
		int money = player->getMoney();

		ge.setSplit(false);
		ge.setStand(false);

		bool firstTurnFlag = true;
		bool keepMainLoopGoing = true;

		bool firstHandBusted = false;
		bool secondHandBusted = false;
		bool dealerHandBusted;
		int playerTotal1;

		do
		{
			dealerHandBusted = false;
			playerTotal1 = player->Person::calculateTotalAndPrintHand(player->getPlayerHand(), player->getPlayerHandValues(), true, "Player");

			if (player->getPlayerHand().at(0).getValue() == player->getPlayerHand().at(1).getValue() && firstTurnFlag && ge.getPlayerBet() * 2 < money)
			{
				ge.setSplit(true);
			}
			else
			{
				ge.setSplit(false);
			}

			if (dealer->getDealerHand().at(0).getValue() == 1 && firstTurnFlag)
			{
				ge.setInsurance(true);
			}
			else
			{
				ge.setInsurance(false);
			}

			if (ge.getPlayerBet() * 2 < money && firstTurnFlag)
			{
				ge.setDouble(true);
			}
			else
			{
				ge.setDouble(false);
			}

			firstTurnFlag = false;

			bool repeatLoopForUserInput = true;

			//REPLACE WITH REAL USER INPUT

			do
			{
				ge.menuPrintingControl();

				ge.setUserInputForMenu(ge.receiveUserMenuInput());

				repeatLoopForUserInput = ge.validateUserMenuInput();
				cout << "\n";

				if (!repeatLoopForUserInput)
				{
					cout << "The option you entered: " << ge.getUserInputForMenu() << " is invalid. \n\n";
				}

			} while (!repeatLoopForUserInput);

			if (ge.getUserInputForMenu().compare("h") == 0 || ge.getUserInputForMenu().compare("H") == 0)
			{
				if (!ge.getSplit())
				{
					cout << "Player hits.\n";
					ge.hitMethod(deckCards, player->getPlayerHand());
					playerTotal1 = player->Person::calculateTotalAndPrintHand(player->getPlayerHand(), player->getPlayerHandValues(), true, "Player");
				}
				else
				{
					//TODO: add code for hitting with two hands
				}
			}
			else if (ge.getUserInputForMenu().compare("s") == 0 || ge.getUserInputForMenu().compare("S") == 0)
			{
				cout << "Player stays.\n";
				break;
			}
			else if (ge.getUserInputForMenu().compare("d") == 0 || ge.getUserInputForMenu().compare("D") == 0)
			{
				cout << "Player hits.\n";
				ge.setPlayerBet(ge.getPlayerBet() * 2);
				ge.hitMethod(deckCards, player->getPlayerHand());
				playerTotal1 = player->Person::calculateTotalAndPrintHand(player->getPlayerHand(), player->getPlayerHandValues(), true, "Player");
				break;
			}
			else if (ge.getUserInputForMenu().compare("p") == 0 || ge.getUserInputForMenu().compare("P") == 0)
			{
				ge.splitCards(player->getPlayerHand(), player->getPlayerHand2());
				ge.setSplit(true);
			}
			else if (ge.getUserInputForMenu().compare("i") == 0 || ge.getUserInputForMenu().compare("I") == 0)
			{
				//TODO: google these rules...
			}

			if (playerTotal1 > 21)
			{
				firstHandBusted = true;

				if (!ge.getSplit())
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

			if (ge.getSplit()) //check that none of the hands have busted
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

		if (ge.getSplit()) //check that none of the hands have busted
		{
			if (player->Person::calculateTotalAndPrintHand(player->getPlayerHand2(), player->getPlayerHandValues2(), false, "Player") > 21)
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
				cout << "Player's hand is " << playerTotal1 << ". Player has busted.\nPlayer has lost $" << ge.getPlayerBet() << "\n";
				player->setMoney(money - ge.getPlayerBet());
			}
			else
			{
				//prints dealer's hand and calculates its value
				dealersTotal = dealer->Person::calculateTotalAndPrintHand(dealer->getDealerHand(), dealer->getDealerHandValues(), true, "Dealer");

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
					ge.hitMethod(deckCards, dealer->getDealerHand());
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
					cout << "Dealer has a higher hand. You have lost $" << ge.getPlayerBet() << ".\n";
					player->setMoney(money - ge.getPlayerBet());
				}
				else if (dealersTotal == playerTotal1)
				{
					cout << "Dealer and Player are tied. No money was lost/earnt.\n";
				}
				else if (playerTotal1 > dealersTotal)
				{
					cout << "Player has a higher hand. You have won $" << ge.getPlayerBet() << ".\n";
					player->setMoney(money + ge.getPlayerBet());
				}
			}
			else
			{
				cout << "You have won $" << ge.getPlayerBet() << ".\n";
				player->setMoney(money + ge.getPlayerBet());
			}
		}

		if (player->getMoney() <= 0)
		{
			cout << "\n GAME OVER\n\n You have run out of money. Insert more money to play again.\n";
			exit(0);
		}
		*/
		window.clear();

		//betting controls
		if (showBettingGUI)
		{
			window.draw(enterBetButton);
			window.draw(increaseBetButton);
			window.draw(decreaseBetButton);
			window.draw(playerCurrentBetText);
		}

		if (showUserButtons)
		{
			window.draw(hitButton);
			window.draw(insuranceButton);
			window.draw(splitButton);
			window.draw(stayButton);
			window.draw(doubleDownButton);
		}

		//always shown
		window.draw(playerCurrentMoneyText);

		for (vector<sf::Sprite>::iterator it = cardsToRender.begin(); it != cardsToRender.end(); ++it)
		{
			window.draw(*it);
		}

		//ADD DEALLOCATING CODE FOR CARDSTORENDER AND ITS TEXTURES!!!!!!!!!!!!!!!

		//display window
		window.display();
	}
}
