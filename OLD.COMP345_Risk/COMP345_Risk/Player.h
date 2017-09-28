#pragma once
#include "Dice.h"
#include <iostream>
using namespace std;

class Player {
public:
	Player(int id);
	~Player();
	//Dice *dice;
	//Dice getDice();
	int getId();
	void setId(int newId);
	int getDiceRolled();
	void showStats();
	void setDiceRolled(int dice);
	void roll(int num);
private:
	int id;
	int diceRolled;
	int diceDistribution[6];
};

