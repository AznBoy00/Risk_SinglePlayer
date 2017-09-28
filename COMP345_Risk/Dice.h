#pragma once
#include "Player.h"

class Dice {
public:
	Dice();
	~Dice();
	void rollDice(int num);
	int rollDiceOnce();
private:
	int diceRollDistribution[6];
};