#pragma once
class Card
{

private:
	int _suit;
	int _value;

public:
	Card(int val, int sui);

	void setSuit(int s);
	void setValue(int v);

	int getValue(){ return _value; }
	int getSuit(){ return _suit; }

	void printCardValueAndSuit();

	~Card();
};

