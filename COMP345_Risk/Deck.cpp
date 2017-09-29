#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <string>
#include "deck.h"
#include "GameConstants.h"

// create all country cards here based on the map that is loaded.
//do not know which countries are what type for now.
Deck::Deck() {
	for (int count = 0; count < numberOfCards; count++) {//create a deck with cards. 
		Card* c = new Card("Quebec", "Infantry");
		cardDeck.push_back(*c);
	}
}

Deck::~Deck() {
}

Card Deck::draw() {
	shuffle();
	Card top = cardDeck.back();
	cardDeck.pop_back();
	return top;
}

void Deck::shuffle() {
	std::random_shuffle(cardDeck.begin(), cardDeck.end());
}

Card::Card(string c, string t) {
	country = c;
	type = t;
}

string Card::getType(int card) {
	return type;
}


/*void Deck::shuffle() {//shuffle created deck
	int currentCard;
	Deck temp;
	for (int first = 0; first < numberOfCountry; first++) {
		int second = (rand() + time(0)) + time(0) % numberOfCountry;
		//Card temp = deck[first];
		deck[first] = deck[second];
		deck[second] = temp;

	}
}*/

string Deck::hand() {
	Deck();
	this->shuffle();
	//deck player1[];
	//deck player2[];
	//deck player3[];
	//deck player4[];
	//deck player5[];
	//deck player6[];
	return NULL;
}
