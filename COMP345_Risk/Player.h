#pragma once
#include "Dice.h"
#include <iostream>
using namespace std;

class Player {
public:
	//Constructors
	Player(int id);
	~Player();

	//Object Variables
	Dice* dice;
	Dice getDice();

	//Platyer Variables
	string countries;
	
	//Getters and Setters
	int getId();
	void setId(int newId);
	int getDiceRolled();
	void setDiceRolled(int dice);

	//Player Actions & MISC
	void roll(int num);
	void reinforce();
	void attack();
	void fortify();
	void showStats();
private:
	//Player Variables
	int id;
	int diceRolled;
	int diceDistribution[6];
};

