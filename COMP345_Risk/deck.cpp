#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include "deck.h"



int numberOfCountry = 0; // changable depending on the map. 

class deck {

	string countryCard, cardType;


	string deck::card(string country, string type) {
		countryCard = country;
		cardType = type;
		numberOfCountry = 
			for (count = 0; count < numberOfCountry; count++) {
			country[numberOfCountry];
				 type[numberOfCountry];
			}
	}
  
	string deck::getType(card) {
		return cardType;
	}

	string deck::print() {
		return (countryCard + ", " + cardType);
	}
	// create all country cards here based on the map that is loaded.
	//do not know which countries are what type for now.
	
	deck::deck() {
		deck = new card[numberOfCountry];
		int currentCard = 0;
		for (int count = 0; count < numberOfCountry; count++) {//create a deck with cards. 
			deck[count] = card(country[count],type[count]);
		}
	}

	void deck::shuffle() {//shuffle created deck
		currentCard = 0;
		for (int first = 0; first < numberOfCountry; first++) {
			int second = (rand() + time(0)) + time(0) % numberOfCountry;
			card temp = deck[first];
			deck[first] = deck[second];
			deck[second] = temp;

		}
	}

	string deck::hand(){
		deck();

		deck.shuffle(); 
	    deck player1[];
		deck player2[];
		deck player3[];
		deck player4[];
		deck player5[];
		deck player6[];
	}

	string deck::draw() {

		int currentCard = 0; 
		turnplayer[currentCard] = deck[currentCard]; // turnplayer to be define in player file. 
		currentCard++;
	}

	string deck::exchange() {
		int exchangeCount = 0;
		int card1;
		int card2;
		int card3;
		int army;
		if (turnplayer[card1.getType()]==turnplayer[card2.getType()]==turnplayer[card3.getType()]){
			// remove 3 cards from player's hand, and give army based on the number of exchanges done so far. 
			army = 4 + exchangeCount * 2;
			exchangeCount++;
		}
		else army = 15;
		
	string deck::driver() {

	};


	void deck::printdeck() {
		for (int i = 0; i < numberOfCountry; i++) {
			cout << deck[i].print();
		}
	}


};




