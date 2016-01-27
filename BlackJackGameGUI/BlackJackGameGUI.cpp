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

//card pixel size constants
const int CARD_SPRITE_WIDTH = 73;
const int CARD_SPRITE_HEIGHT = 98;

//user's position for cards
int userCardXPosition = 300;
int userCardYPosition = 400;

//dealer's position for cards
int firstXPositionOfCards = 0;
int firstYPositionOfCards = 0;

//Vital variable for game flow and loop control 
int gameStage = 0;

sf::Font font;
vector<sf::Sprite> cardsToRender;

//player stat variables
int playerCurrentBet = 0;
int playerMoneyCounter = 500;
int playerTurnNumber = 0;

//button declaration
Button enterBetButton(font, { 70.f, 70.f });
Button increaseBetButton(font, { 70.f, 70.f });
Button decreaseBetButton(font, { 70.f, 70.f });
Button hitButton(font, { 70.f, 70.f });
Button stayButton(font, { 70.f, 70.f });
Button splitButton(font, { 110.f, 70.f });
Button insuranceButton(font, { 160.f, 70.f });
Button doubleDownButton(font, { 200.f, 70.f });
Button playAgainButton(font, { 200.f, 70.f });

//string declaration
sf::Text playerCurrentBetText(to_string(playerCurrentBet), font);
sf::Text playerCurrentMoneyText("Player's Money: " + to_string(playerMoneyCounter), font);
sf::Text dealerHandText("Dealer's Hand", font);
sf::Text playerHandText("Player's Hand", font);
sf::Text playerBustedText("Player has busted", font);
sf::Text dealerBustedText("Dealer has busted", font);
sf::Text dealerTotalText("Total:", font);
sf::Text playerTotalText("Total:", font);
sf::Text gameStatusText("", font);
sf::Text playerEarningsText("Player has earned", font);
sf::Text gameOverText("", font);

//show button flags
bool showBettingGUI = true; //Shows the bet and increase/decrease bet buttons
bool showUserButtons = false;
bool showDoubleDown = false;
bool showHit = true; //hit is always available
bool showInsurance = false;
bool showSplit = false;
bool showStay = true;
bool showPlayAgainButton = false;

//show text flags
bool showPlayerHandText = false;
bool showDealerHandText = false;
bool showPlayerBustedText = false;
bool showDealerBustedText = false;
bool showdealerTotalText = false;
bool showPlayerTotalText = false;
bool showGameStatusText = false;
bool showPlayerEarningsText = false;
bool showGameOverText = false;

//user input flags
bool userHits = false;
bool userStays = false;
bool userSplits = false;
bool userInsures = false;
bool userDoubleDowns = false;

//user status flags
bool userHasSplit = false;

void betAction()
{
	if (playerCurrentBet == 0)
	{
		return;
	}

	//triggered method
	showBettingGUI = false;
	showUserButtons = true;
	gameStage = 1; //move to stage 1
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
	userHits = true;
	playerTurnNumber++;
}

void splitAction()
{
	userSplits = true;
	playerTurnNumber++;
}

void stayAction()
{
	userStays = true;
	playerTurnNumber++;
}

void insuranceAction()
{
	userInsures = true;
	playerTurnNumber++;
}

void doubleDownAction()
{
	userDoubleDowns = true;
	playerTurnNumber++;
}

void playAgainAction()
{
	showBettingGUI = true;
	playerCurrentBet = 0;
	showDealerHandText = false;
	showPlayerHandText = false;
	showPlayerTotalText = false;
	showdealerTotalText = false;
	showGameStatusText = false;
	showGameOverText = false;
	showPlayAgainButton = false;
	playerCurrentBetText.setString(to_string(playerCurrentBet));
	cardsToRender.erase(cardsToRender.begin(), cardsToRender.end());
}

vector<sf::Sprite> createFirstRoundCardSprites(vector<Card> givenCards, int type)
{
	vector<sf::Sprite> createdSprites;

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

		case 1: //player first time
		{
			firstXPositionOfCards = userCardXPosition;
			firstYPositionOfCards = userCardYPosition;
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

		if (type == 1)
		{
			userCardXPosition += 80;
		}

		Card currentCard = *it;
		sf::Texture* newTexture = new sf::Texture();
		newTexture->loadFromFile("CardsSprite.png");
		sf::Sprite* newCard = new sf::Sprite(*newTexture);
		newCard->setTextureRect(sf::IntRect((currentCard.getValue() - 1)*CARD_SPRITE_WIDTH, (currentCard.getSuit() - 1) * CARD_SPRITE_HEIGHT, CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT));
		newCard->setPosition(firstXPositionOfCards, firstYPositionOfCards);
		createdSprites.push_back(*newCard);
	}
	return createdSprites;
}

sf::Sprite createPlayerCardSprite(Card currentCard, int yPosition, int xPosition)
{
	sf::Texture* newTexture = new sf::Texture();
	newTexture->loadFromFile("CardsSprite.png");
	sf::Sprite* newCard = new sf::Sprite(*newTexture);
	newCard->setTextureRect(sf::IntRect((currentCard.getValue() - 1)*CARD_SPRITE_WIDTH, (currentCard.getSuit() - 1) * CARD_SPRITE_HEIGHT, CARD_SPRITE_WIDTH, CARD_SPRITE_HEIGHT));
	newCard->setPosition(yPosition, xPosition);
	return *newCard;
}

int main()
{
	//setting up game
	unique_ptr<Player> player(new Player());
	player->setMoney(playerMoneyCounter);
	unique_ptr<Deck> deck(new Deck());
	unique_ptr<Dealer> dealer(new Dealer());
	unique_ptr<GameEngine> gameEngine(new GameEngine());

	//loading font
	font.loadFromFile("whitrabt.ttf");

	dealerHandText.setCharacterSize(30);
	dealerHandText.setStyle(sf::Text::Bold);
	dealerHandText.setColor(sf::Color::White);
	dealerHandText.setPosition(300, 130);

	playerHandText.setCharacterSize(30);
	playerHandText.setStyle(sf::Text::Bold);
	playerHandText.setColor(sf::Color::White);
	playerHandText.setPosition(380, 335);

	dealerBustedText.setCharacterSize(30);
	dealerBustedText.setStyle(sf::Text::Bold);
	dealerBustedText.setColor(sf::Color::White);
	dealerBustedText.setPosition(145, 10);

	dealerTotalText.setCharacterSize(30);
	dealerTotalText.setStyle(sf::Text::Bold);
	dealerTotalText.setColor(sf::Color::White);
	dealerTotalText.setPosition(580, 130);

	playerTotalText.setCharacterSize(30);
	playerTotalText.setStyle(sf::Text::Bold);
	playerTotalText.setColor(sf::Color::White);
	playerTotalText.setPosition(630, 335);

	gameStatusText.setCharacterSize(30);
	gameStatusText.setStyle(sf::Text::Bold);
	gameStatusText.setColor(sf::Color::White);
	gameStatusText.setPosition(333, 550);

	playerEarningsText.setCharacterSize(30);
	playerEarningsText.setStyle(sf::Text::Bold);
	playerEarningsText.setColor(sf::Color::White);
	playerEarningsText.setPosition(145, 10);

	gameOverText.setCharacterSize(30);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setColor(sf::Color::White);
	gameOverText.setPosition(500, 700);

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
	playAgainButton.setString("Play Again");

	//set button position
	enterBetButton.setPosition(320, 0);
	increaseBetButton.setPosition(250, 0);
	decreaseBetButton.setPosition(0, 0);
	hitButton.setPosition(350,700);
	stayButton.setPosition(420,700);
	splitButton.setPosition(490,700);
	insuranceButton.setPosition(600,700);
	doubleDownButton.setPosition(760, 700);
	playAgainButton.setPosition(333,650);

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

	playAgainButton.setBackgroundColor(sf::Color(59, 134, 134));
	playAgainButton.setTextColor(sf::Color(11, 72, 107));
	playAgainButton.setOverBackgroundColor(sf::Color(121, 189, 154));
	playAgainButton.setOverTextColor(sf::Color(207, 240, 158));
	playAgainButton.setOverOutlineColor(sf::Color(168, 219, 168));

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

	playAgainButton.setOutlineThickness(1.f);
	playAgainButton.setOutlineColor(sf::Color(168, 219, 168));

	//set trigger functions
	enterBetButton.setTriggerFunction(betAction);
	increaseBetButton.setTriggerFunction(increaseAction);
	decreaseBetButton.setTriggerFunction(decreaseAction);
	hitButton.setTriggerFunction(hitAction);
	stayButton.setTriggerFunction(stayAction);
	splitButton.setTriggerFunction(splitAction);
	insuranceButton.setTriggerFunction(insuranceAction);
	doubleDownButton.setTriggerFunction(doubleDownAction);
	playAgainButton.setTriggerFunction(playAgainAction);

	sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");

	GameEngine ge = *gameEngine;
	vector<Card> deckCards = deck->getDeckCards();
	int money = player->getMoney();

	bool firstTurnFlag = true;
	bool keepMainLoopGoing = true;

	bool firstHandBusted = false;
	bool secondHandBusted = false;
	bool dealerHandBusted = false;
	int playerTotal1 = 0;
	int playerTotal2 = 0;

	int dealersTotal = 0;

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
			hitButton.events(event);
			splitButton.events(event);
			stayButton.events(event);
			insuranceButton.events(event);
			doubleDownButton.events(event);
			playAgainButton.events(event);
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
		playAgainButton.handler(window);
		
		playerCurrentMoneyText.setString("Player's Money: " + to_string(playerMoneyCounter));

		//game engine action
		if (gameStage == 1)
		{
			//reset these variables
			firstTurnFlag = true;
			keepMainLoopGoing = true;

			firstHandBusted = false;
			secondHandBusted = false;
			dealerHandBusted = false;
			playerTotal1 = 0;
			playerTotal2 = 0;
			userCardXPosition = 300;
			userCardYPosition = 400;

			showPlayerBustedText = false;
			showDealerBustedText = false;
			showdealerTotalText = false;
			showPlayerTotalText = false;
			showGameStatusText = false;
			showPlayerEarningsText = false;
			showGameOverText = false;

			showPlayAgainButton = false;

			gameStage++;
			playerTurnNumber = 0; //resets the player turn counter
			gameEngine->setPlayerBet(playerCurrentBet);

			player->emptyHand(player->getPlayerHand());
			player->emptyHand(player->getPlayerHand2());
			dealer->emptyHand(dealer->getDealerHand());

			dealer->dealCards(deck->getDeckCards(), player->getPlayerHand());

			cardsToRender.erase(cardsToRender.begin(), cardsToRender.end());

			vector<sf::Sprite> dealerSprites = createFirstRoundCardSprites(dealer->printDealerHandWithHiddenCard(), 0);
			cardsToRender.insert(cardsToRender.end(), dealerSprites.begin(), dealerSprites.end());
			vector<sf::Sprite> playerSprites = createFirstRoundCardSprites(player->getPlayerHand(), 1);
			cardsToRender.insert(cardsToRender.end(), playerSprites.begin(), playerSprites.end());

			//show the dealer hand text
			showDealerHandText = true;
			showPlayerHandText = true;
		}

		if (gameStage == 2)
		{
			gameStage++;
			if (player->getPlayerHand().at(0).getValue() == player->getPlayerHand().at(1).getValue() && playerTurnNumber == 0 && ge.getPlayerBet() * 2 < money)
			{
				showSplit = true;
			}
			else
			{
				showSplit = false;
			}

			if (dealer->getDealerHand().at(0).getValue() == 1 && playerTurnNumber == 0)
			{
				showInsurance = true;
			}
			else
			{
				showInsurance = false;
			}

			if (ge.getPlayerBet() * 2 < money && playerTurnNumber == 0)
			{
				showDoubleDown = true;
			}
			else
			{
				showDoubleDown = false;
			}
		}

		if (gameStage == 3)
		{
			playerTotal1 = player->Person::calculateTotalAndPrintHand(player->getPlayerHand(), player->getPlayerHandValues(), false, "Player");

			if (userHits)
			{
				userHits = false;
				if (!userHasSplit)
				{
					userCardXPosition += 80;
					sf::Sprite playerSprite = createPlayerCardSprite(ge.hitMethod(deckCards, player->getPlayerHand()), userCardXPosition, userCardYPosition);
					cardsToRender.push_back(playerSprite);
					playerTotal1 = player->Person::calculateTotalAndPrintHand(player->getPlayerHand(), player->getPlayerHandValues(), false, "Player");
				}
				else
				{
					//TODO: add code for hitting with two hands
				}
			}
			else if (userStays)
			{
				userStays = false;
				gameStage++;
			}
			else if (userDoubleDowns)
			{
				userDoubleDowns = false;
				playerCurrentBet = playerCurrentBet * 2;
				ge.hitMethod(deckCards, player->getPlayerHand());
				playerTotal1 = player->Person::calculateTotalAndPrintHand(player->getPlayerHand(), player->getPlayerHandValues(), false, "Player");
				gameStage++;
			}
			else if (userSplits)
			{
				userSplits = false;
				ge.splitCards(player->getPlayerHand(), player->getPlayerHand2());
				userHasSplit = true;
			}
			else if (userInsures)
			{
				userInsures = false;
				//TODO: google these rules...
			}

			//update player's total
			playerTotalText.setString("Total: " + to_string(playerTotal1));
			showPlayerTotalText = true;

			if (playerTotal1 > 21)
			{
				firstHandBusted = true;

				if (!userHasSplit)
				{
					gameStage++;
				}
				else
				{
					if (firstHandBusted && secondHandBusted)
					{
						gameStage++;
					}
				}
			}

			if (userHasSplit) //check that none of the hands have busted
			{
				if (playerTotal2 > 21)
				{
					secondHandBusted = true;

					if (firstHandBusted && secondHandBusted)
					{
						break;
					}
				}
			}
		}

		if (gameStage == 4)
		{
			dealersTotal = 0;
			bool keepLoopGoing = false;
			showUserButtons = false;
			vector<Card> dealersCards = dealer->getDealerHand();

			if (firstHandBusted)
			{
				player->setMoney(money - playerCurrentBet);
			}
			else
			{
				//show dealer's hand
				cardsToRender.erase(cardsToRender.begin()); //deletes the dealer's card that is backward
				firstXPositionOfCards = 300;
				firstYPositionOfCards = 200;
				for (vector<Card>::iterator it = dealersCards.begin() + 1; it != dealersCards.end(); ++it)
				{
					firstXPositionOfCards += 80;
					cardsToRender.push_back(createPlayerCardSprite(*it, firstXPositionOfCards, firstYPositionOfCards));
				}
			}

			do
			{
				
				if (!firstHandBusted)
				{
					//prints dealer's hand and calculates its value
					dealersTotal = dealer->calculateTotalAndPrintHand(dealer->getDealerHand(), dealer->getDealerHandValues(), false, "Dealer");

					if (dealersTotal > 21)
					{
						//indicate that dealer has busted
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
						ge.hitMethod(deckCards, dealer->getDealerHand());
						keepLoopGoing = true;
					}
				}

			} while (keepLoopGoing);
			gameStage++;
		}

		if (gameStage == 5)
		{
			if (!firstHandBusted)
			{
				dealerTotalText.setString("Total: " + to_string(dealersTotal));
				showdealerTotalText = true;

				if (!dealerHandBusted)
				{
					if (dealersTotal > playerTotal1)
					{
						gameStatusText.setString("Dealer has a higher hand.\nYou have lost $" + to_string(playerCurrentBet));
						player->setMoney(money - playerCurrentBet);
					}
					else if (dealersTotal == playerTotal1)
					{
						gameStatusText.setString("Dealer and Player are tied.\nNo money was lost/earnt.");
						
					}
					else if (playerTotal1 > dealersTotal)
					{
						gameStatusText.setString("Player has a higher hand.\nYou have won $" + to_string(playerCurrentBet));
						player->setMoney(money + playerCurrentBet);
						playerMoneyCounter += 2*playerCurrentBet;
					}
				}
				else
				{
					gameStatusText.setString("Dealer has busted.\nYou have won $" + to_string(playerCurrentBet));
					player->setMoney(money + playerCurrentBet);
				}
			}
			else
			{
				gameStatusText.setString("Player has busted.\nPlayer has lost $" + to_string(playerCurrentBet));
			}
			showGameStatusText = true;
			gameStage++;
		}

		if (gameStage == 6)
		{
			if (playerMoneyCounter <= 0)
			{
				gameOverText.setString("\n GAME OVER\n\n You have run out of money. Insert more money to play again.\n");
				showGameOverText = true;
				//exit(0);
				//ADD PLAY AGAIN
			}
			else
			{
				showPlayAgainButton = true;
			}
			gameStage++;
		}

		if (gameStage == 7)
		{
			//play again
			
			//exit
		}

		window.clear();

		//betting controls
		if (showBettingGUI)
		{
			window.draw(enterBetButton);
			window.draw(increaseBetButton);
			window.draw(decreaseBetButton);
			window.draw(playerCurrentBetText);
		}

		//shows the main user action buttons
		if (showUserButtons)
		{
			if(showHit) window.draw(hitButton);
			if(showInsurance) window.draw(insuranceButton);
			if(showSplit) window.draw(splitButton);
			if(showStay) window.draw(stayButton);
			if(showDoubleDown) window.draw(doubleDownButton);
		}

		//show play again button
		if (showPlayAgainButton)
		{
			window.draw(playAgainButton);
		}

		//always shown
		window.draw(playerCurrentMoneyText);

		//draw the required texts
		if (showPlayerBustedText) window.draw(playerBustedText);
		if (showDealerBustedText) window.draw(dealerBustedText);
		if (showdealerTotalText) window.draw(dealerTotalText);
		if (showPlayerTotalText) window.draw(playerTotalText);
		if (showGameStatusText) window.draw(gameStatusText);
		if (showPlayerEarningsText) window.draw(playerEarningsText);
		if (showGameOverText) window.draw(gameOverText);
		if (showPlayerHandText) window.draw(playerHandText);
		if (showDealerHandText) window.draw(dealerHandText);

		for (vector<sf::Sprite>::iterator it = cardsToRender.begin(); it != cardsToRender.end(); ++it)
		{
			window.draw(*it);
		}

		//TODO:
		//ADD DEALLOCATING CODE FOR CARDSTORENDER AND ITS TEXTURES!!!!!!!!!!!!!!!

		//display window
		window.display();
	}
}
