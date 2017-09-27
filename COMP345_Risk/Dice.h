#pragma once
#include "Player.h"

class Dice : public Player{
public:
	Dice();
	Dice(int num);
	~Dice();
	void rollDice(int num);

private:
	int diceRollNumber;
	int *diceValue;
	int getDiceRollNumber();
	void setDiceRollNumber(int num);
};

