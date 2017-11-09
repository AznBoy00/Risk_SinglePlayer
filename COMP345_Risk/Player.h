#pragma once
#include "Dice.h"
#include "Map.h"
#include "Cards.h"
#include "Strategy.h"
#include <vector>
#include <iostream>
using namespace std;

class Strategy;

class Player {
public:
	//Constructors
	Player(int id);
	~Player();

	//Object Variables
	Dice getDice();

	//Strats
	enum StrategyType
	{
		AGGRO, PASSIVE, USER
	};
	
	//Getters and Setters
	int getId();
	void setId(int newId);
	int getDiceRolled();
	void setDiceRolled(int dice);

	//Player Actions & MISC
	void roll(int num);
	void showStats();
	void setTurnNumber(int t);
	int getTurnNumber();
	void setOwnedCountry(Country* c) { ownedCountries.push_back(c); }
	void setStrategy(Strategy* strat);
	void executeTurn(Map *map, Deck* deck, vector<Player*> playerVector);
	vector<Country*> getOwnedCountries() { return ownedCountries; }
	Hand* getHand() { return hand; }
private:
	//Player Variables
	int id;
	int diceRolled;
	int diceDistribution[6];
	int turnNumber = 0;
	vector<Country*> ownedCountries;
	Player * findTarget(vector<Player*> playerVector, Country * atkTarget);
	Dice* dice;
	Hand* hand;
	Strategy* strategy;
};

