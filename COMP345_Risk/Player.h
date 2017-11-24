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
	
	//Getters and Setters
	int getId();
	void setId(int newId);
	int getDiceRolled();
	void setDiceRolled(int dice);

	void draw();

	//Player Actions & MISC
	void showStats(Deck* deck);
	void setTurnNumber(int t);
	int getTurnNumber();
	void setOwnedCountry(Country* c) { ownedCountries.push_back(c); }
	void setStrategy(Strategy* strat);
	void setStrategy(Strategy * strat, int strategyId);
	string getState() { return stream.str(); }
	void setConquered(bool c) { conquered = c; }
	bool getConquered() { return conquered; }
	void executeTurn(Map *map, Deck* deck, vector<Player*> playerVector, Game* game);
	vector<Country*> & getOwnedCountries() { return ownedCountries; }
	Hand* getHand() { return hand; }
	stringstream stream;
	void setWinner(bool w) { winner = w; }
	bool getWinner() { return winner; }
	bool isDead() { return dead; }
	int getStrategyId() { return strategyId;  }
private:
	//Player Variables
	int id;
	int diceRolled;
	int diceDistribution[6];
	int strategyId;
	bool conquered;
	//string state;
	int turnNumber = 0;
	bool winner = false;
	bool dead = false;
	
	vector<Country*> ownedCountries;
	Player * findTarget(vector<Player*> playerVector, Country * atkTarget);
	Dice* dice;
	Hand* hand;
	Strategy* strategy;
};

