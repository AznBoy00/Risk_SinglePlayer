#include "Cards.h"
#include "GameConstants.h"
#include <iostream>
#include <vector>
using namespace std;

Cards::Cards() {
}

Cards::Cards(int type, int id, int location) {
	this->type = type;
	this->cardID = id;
	this->location = location;
}

int Cards::getId() {
	return this->cardID;
}

int Cards::getType() {
	return this->type;
}

int Cards::getCardLocation() {
	return this->location;
}

void Cards::setCardLocation(int value) {
	this->location = value;
}

Deck::Deck() {
	for (int i = 0; i < DECK_SIZE; i++) {
		if (i < CARDS_PER_TYPE) {
			cards[i] = Cards(1, i + 1, 0);
		}
		else if (i < 2 * CARDS_PER_TYPE) {
			cards[i] = Cards(2, i + 1, 0);
		}
		else if (i < 3 * CARDS_PER_TYPE) {
			cards[i] = Cards(3, i + 1, 0);
		}
	}
	//debug display deck array
	showCardsInDeck(this);
}

void Deck::showCardsInDeck(Deck* deck) {
	cout << "Deck card content:" << endl;
	for (size_t i = 0; i < DECK_SIZE; i++) {
		if (deck->cards[i].getCardLocation() == 0) {
			cout << "Card ID at position " << i << " (TYPE-ID): " << deck->cards[i].getType() << "-" << deck->cards[i].getId() << endl;
		}
	}
}

void Deck::showCardsInDiscarded(Deck* deck) {
	cout << "Discarded card content:" << endl;
	for (size_t i = 0; i < DECK_SIZE; i++) {
		if (deck->cards[i].getCardLocation() == -1) {
			cout << "Card ID at position " << i << " (TYPE-ID): " << deck->cards[i].getType() << deck->cards[i].getId() << endl;
		}
	}
}

void Deck::showCardsInHand(int handId, Deck* deck) {
	cout << "Player " << handId << "'s hand:" << endl;
	for (size_t i = 0; i < 42; i++) {
		if (deck->cards[i].getCardLocation() == handId) {
			cout << "Card in hand(TYPE-ID): " << deck->cards[i].getType() << deck->cards[i].getId() << endl;
		}
	}
}

void Deck::draw(int handId, Deck* deck) {
	cout << "Drawing cards for player " << handId << endl;
	for (size_t i = 0; i < DECK_SIZE; i++) {
		if (deck->cards[i].getCardLocation() == 0) {
			deck->cards[i].setCardLocation(handId);
			break;
		}
	}
}

// NOT KEVIN's

Hand::Hand(int id) {
	this->id = id;
}

void Hand::showCardsInHand(int handId, Deck deck) {
	cout << "Player " << handId << "'s hand:" << endl;
	for (size_t i = 0; i < 42; i++) {
		if (deck.cards[i].getCardLocation() == handId) {
			cout << "Card ID at position " << i << " (TYPE-ID): " << deck.cards[i].getType() << deck.cards[i].getId() << endl;
		}
	}
}

//Bottom Added

int Hand::cardsInHand(int handId, Deck* deck) {
	int cardsInHand = 0;
	for (unsigned int i = 0; i < 42; i++) {
		if (deck->cards[i].getCardLocation() == handId) {
			cardsInHand++;
		}
	}
	return cardsInHand;
}

int Hand::exchange(int handId, Deck* deck) {
	vector<Cards> CardHand;

	for (unsigned int i = 0; i < 42; i++) {
		if (deck->cards[i].getCardLocation() == handId) {
			CardHand.push_back(deck->cards[i]);
		}
	}

	int infantry = 0, artillery = 0, cavalry = 0;

	for (unsigned int i = 0; i < CardHand.size(); i++) {
		if (deck->cards[i].type == 1) {
			infantry++;
		}
		else if (deck->cards[i].type == 2) {
			artillery++;
		}
		else {
			cavalry++;
		}
	}

	int discardInfantry = 0, discardArtillery = 0, discardCavalry = 0;

	if (infantry > 3) {
		for (unsigned int i = 0; i < CardHand.size() && discardInfantry < 3; i++) {
			if (deck->cards[i].type == 1) {
				deck->cards[i].setCardLocation(-1);
				discardInfantry++;
			}
		}
		exchangeArmies += 5;
		cout << "You will be receiving " << exchangeArmies << " armies." << endl;
		return exchangeArmies;
	}
	else if (artillery > 3) {
		for (unsigned int i = 0; i < CardHand.size() && discardArtillery < 3; i++) {
			if (deck->cards[i].type == 2) {
				deck->cards[i].setCardLocation(-1);
				discardArtillery++;
			}
		}
		exchangeArmies += 5;
		cout << "You will be receiving " << exchangeArmies << " armies." << endl;
		return exchangeArmies;
	}
	else if (cavalry > 3) {
		for (unsigned int i = 0; i < CardHand.size() && discardCavalry < 3; i++) {
			if (deck->cards[i].type == 3) {
				deck->cards[i].setCardLocation(-1);
				discardCavalry++;
			}
		}
		exchangeArmies += 5;
		cout << "You will be receiving " << exchangeArmies << " armies." << endl;
		return exchangeArmies;
	}
	else if (infantry > 1 || artillery > 1 || cavalry > 1) {
		for (unsigned int i = 0; i < CardHand.size(); i++) {
			if (deck->cards[i].type == 1 && discardInfantry == 0) {
				deck->cards[i].setCardLocation(-1);
				discardInfantry++;
			}
			else if (deck->cards[i].type == 2 && discardArtillery == 0) {
				deck->cards[i].setCardLocation(-1);
				discardArtillery++;
			}
			else if (deck->cards[i].type == 3 && discardCavalry == 0) {
				deck->cards[i].setCardLocation(-1);
				discardCavalry++;
			}
		}
		exchangeArmies += 5;
		cout << "You will be receiving " << exchangeArmies << " armies." << endl;
		return exchangeArmies;
	}
	else {
		cout << "You can't exchange yet" << endl;
		return 0;
	}

}
