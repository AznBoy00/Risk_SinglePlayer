#pragma once
class Cards {
public:
	Cards();
	Cards(int type, int id, int location);

	int type; //0 = NULL, 1 = infantry, 2 = artillery, 3 = cavalry
	int cardID;
	int location; //0 = Deck, X = Player X's hand

	int getType();
	int getId();
	int getCardLocation();
};

class Deck {
public:
	Deck();

	Cards cards[42];

	void draw();
	void showCardsInDeck();

private:
	int const DECK_SIZE = 42;
	int const CARDS_PER_TYPE = DECK_SIZE / 3;
	int const CARD_TYPES = 3;
	int remainingCards;
};

class Hand {
	Hand();

};

