#pragma once
#include "Dice.h"
#include <vector>
#include <iostream>
#include "Map.h"
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
	void setTurnNumber(int t);
	int getTurnNumber();
	void setOwnedCountry(Country* c) { ownedCountries.push_back(c); }
	vector<Country*> getOwnedCountries() { return ownedCountries; }
private:
	//Player Variables
	int id;
	int diceRolled;
	int diceDistribution[6];
	int turnNumber = 0;
	vector<Country*> ownedCountries;
};

