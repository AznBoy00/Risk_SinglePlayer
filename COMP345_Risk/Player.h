#pragma once
#include "Dice.h"

class Player {
public:
	Player();
	Player(int id); // Main constructor
	~Player();
	Dice getDice();
	int getId();
	void setId(int newId);
private:
	int id;
	Dice *dice;
};

