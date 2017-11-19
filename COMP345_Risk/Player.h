#pragma once
#include "Dice.h"
#include "Map.h"
#include "Cards.h"
#include "Strategy.h"
#include "Subject.h"
#include "Game.h"
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

class Strategy;
class Game;

class Player : public Subject{
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
	void showStats(Deck* deck);
	void setTurnNumber(int t);
	int getTurnNumber();
	void setOwnedCountry(Country* c) { ownedCountries.push_back(c); }
	void setStrategy(Strategy* strat);
	string getState() { return stream.str(); }
	void setConquered(bool c) { conquered = c; }
	bool getConquered() { return conquered; }
	void executeTurn(Map *map, Deck* deck, vector<Player*> playerVector, Game* game);
	vector<Country*> getOwnedCountries() { return ownedCountries; }
	Hand* getHand() { return hand; }
	stringstream stream;
private:
	//Player Variables
	int id;
	int diceRolled;
	int diceDistribution[6];
	bool conquered;
	//string state;
	int turnNumber = 0;
	
	vector<Country*> ownedCountries;
	Player * findTarget(vector<Player*> playerVector, Country * atkTarget);
	Dice* dice;
	Hand* hand;
	Strategy* strategy;
};

