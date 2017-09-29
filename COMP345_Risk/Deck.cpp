#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include "deck.h"
#include "GameConstants.h"

// create all country cards here based on the map that is loaded.
//do not know which countries are what type for now.
Deck::Deck() {
	//deck = new Card[numberOfCountry];
	int currentCard = 0;
	for (int count = 0; count < numberOfCountry; count++) {//create a deck with cards. 
		//deck[count] = card(country[count], type[count]);
	}
}

Deck::~Deck() {
}


string Deck::card(string country, string type) {
	countryCard = country;
	cardType = type;
	numberOfCountry;
	for (int count = 0; count < numberOfCountry; count++) {
		country[numberOfCountry];
		type[numberOfCountry];
	}
	return NULL;
}

string Deck::getType(int card) {
	return cardType;
}

string Deck::print() {
	return (countryCard + ", " + cardType);
}

void Deck::shuffle() {//shuffle created deck
	int currentCard;
	Deck temp;
	for (int first = 0; first < numberOfCountry; first++) {
		int second = (rand() + time(0)) + time(0) % numberOfCountry;
		//Card temp = deck[first];
		deck[first] = deck[second];
		deck[second] = temp;

	}
}

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

string Deck::draw() {
	int currentCard = 0;
	//turnplayer[currentCard] = deck[currentCard]; // turnplayer to be define in player file. 
	currentCard++;
	return NULL;
}