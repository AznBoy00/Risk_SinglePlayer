#pragma once
#include "Dice.h"
#include "Map.h"
#include "Cards.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "Subject.h"
using namespace std;

class Player : public Subject{
public:
	//Constructors
	Player(int id);
	~Player();

	//Object Variables
	Dice getDice();

	//Player Variables
	
	//Getters and Setters
	int getId();
	void setId(int newId);
	int getDiceRolled();
	void setDiceRolled(int dice);

	//Player Actions & MISC
	void roll(int num);
	void reinforce(Map* map, Deck* deck);
	void attack(Map * map, vector<Player*> playerVector);
	void fortify();
	void showStats();
	void setConquered(bool b) { conquered = b; }
	void setTurnNumber(int t);
	int getTurnNumber();
	string getState() { return stream.str(); }
	bool getConquered() { return conquered; }
	void setOwnedCountry(Country* c) { ownedCountries.push_back(c); }
	vector<Country*> getOwnedCountries() { return ownedCountries; }
private:
	//Player Variables
	int id;
	int diceRolled;
	int diceDistribution[6];
	bool conquered;
	//string state;
	stringstream stream;
	int turnNumber = 0;
	vector<Country*> ownedCountries;
	Player * findTarget(vector<Player*> playerVector, Country * atkTarget);
	void attackDo(Country* atkFrom, Country* atkTarget, Map* map, vector<Player*> playerVector);
	Dice* dice;
	Hand* hand;
};

