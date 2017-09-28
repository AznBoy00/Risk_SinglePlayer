#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include "deck.h"


using namespace std;

int numberOfCountry = 0; // changable depending on the map. 



class deck {

	string countryCard, cardType;

	deck::card(string country, string type) {
		countryCard = country;
		cardType = type;
		numberOfCountry = 
			for (count = 0; count < numberOfCountry; count++) {
			country[numberOfCountry];
				 type[numberOfCountry];
			}
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
		deck().shuffle(); 

	}

	string deck::draw() {
	}

	string deck::exchange() {
	}

	void deck::printdeck() {
		for (int i = 0; i < numberOfCountry; i++) {
			cout << deck[i].print();
		}
	}


};




