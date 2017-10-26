#include <iostream>
using namespace std;

class GameConstants {
public:
	int const STARTING_NUMBER_OF_COUNTRY = 5;
	int const DECK_SIZE = 42;
	int const CARDS_PER_TYPE = DECK_SIZE / 3;
	int const CARD_TYPES = 3;
	int const MIN_PLAYER = 2;
	int const MAX_PLAYER = 6;
};