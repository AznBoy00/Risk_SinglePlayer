<<<<<<< HEAD
#pragma once

class Dice{
public:
	Dice();
	Dice(int num);
	~Dice();
	void rollDice(int num);
	int getDiceRollNumber();
	void setDiceRollNumber(int num);
private:
	int diceRollNumber;
	int totalDiceRolled;
	int diceRollDistribution[];
};

=======
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

>>>>>>> rev21
