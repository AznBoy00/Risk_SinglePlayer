#pragma once
#include <string>
using namespace std;

class Deck
{
public:
	Deck();
	~Deck();

	Deck* deck;
	int numberOfCountry;
	string countryCard, cardType;

	string card(string country, string type);
	string getType(int card);
	string print();
	string hand();
	string draw();
	string exchange();
	string driver();
	void printdeck();
	void shuffle();
};

