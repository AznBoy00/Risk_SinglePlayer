#pragma once

static int exchangeArmies = 0;

class Cards {
public:
	Cards();
	Cards(int type, int id, int location);

	int type; //0 = NULL, 1 = infantry, 2 = artillery, 3 = cavalry
	int cardID;
	int location; //-1 = Discarded, 0 = Deck, X = Player X's hand

	int getType();
	int getId();
	int getCardLocation();
	void setCardLocation(int value);
};

class Deck {
public:
	Deck();

	Cards cards[42];

	void draw(int handId, Deck* deck);
	void showCardsInDeck(Deck* deck);
	void showCardsInDiscarded(Deck* deck);
	void showCardsInHand(int handId, Deck* deck);
	
	int exchangeHand(int handId, Deck* deck);
	int const DECK_SIZE = 42;
	int const CARDS_PER_TYPE = DECK_SIZE / 3;
	int const CARD_TYPES = 3;
	int remainingCards;
};

class Hand {
public:
	Hand();
	Hand(int id);

	int const DECK_SIZE = 42;
	int id;

	void showCardsInHand(int handId, Deck deck);
	int exchange(int handId, Deck* deck);
	int Hand::cardsInHand(int handId, Deck* deck);
};
