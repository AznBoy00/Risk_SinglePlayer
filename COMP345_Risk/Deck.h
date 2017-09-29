/*#pragma once
#include <string>
#include <vector>
using namespace std;

class Deck
{
public:
	Deck();
	~Deck();

	int numberOfCards;
	vector<Card> cardDeck;
	
	Card draw();
	string driver();
	void printdeck();
	void shuffle();
};

class Card
{
public:
	Card();
	Card(string c, string t);
	string getType();

private:
	string country;
	string type;

};

class Hand
{
public:
	Hand(Deck d);
	void exchange();
private:
	vector<Card> hand;


};*/

