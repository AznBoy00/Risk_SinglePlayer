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
	for (int count = 0; count < 14; count++) {//create a deck with cards. 
		Card* c = new Card("Quebec", "Infantry");
		cardDeck.push_back(*c);
	}
	for (int count = 0; count < 14; count++) {//create a deck with cards. 
		Card* c = new Card("Ontario", "Artillery");
		cardDeck.push_back(*c);
	}
	for (int count = 0; count < 14; count++) {//create a deck with cards. 
		Card* c = new Card("Virginia", "Cavalry");
		cardDeck.push_back(*c);
	}
}

Deck::~Deck() {
}


Card Deck::draw(){
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

string Card::getType() {
	return type;
}

Hand::Hand(Deck d) {
	for (int i = 0; i < 6; i++) {
		hand.push_back(d.draw());
	}
}

void Hand::exchange() {
	for (int i = 0; i < 3; i++) {
		string s = hand.front().getType();
		if (s.compare("Infantry") == 0) {
			cout << "1 army" << endl;
		}
		else if (s.compare("Artillery") == 0) {
			cout << "5 army" << endl;
		}
		else if (s.compare("Cavalry") == 0) {
			cout << "10 army" << endl;
		}
	}
}

