#pragma once
#include <iostream>
#include "Player.h"
#include "MapLoader.h"
#include "Subject.h"
#include "PlayerStatus.h"
using namespace std;

class PlayerStatus;

class Game : public Subject {
public:
	Game();
	void selectMap();
	vector<Player*> playerVector;
	vector<Player*> turnVector;
	MapLoader* loadedMap;
	vector<PlayerStatus*> playersStatus;
	int turnCounter = 0;
	void initializePlayers();
	void assignTurns();
	void startGame();
	void assignCountries();
	void assignArmies();
private:
	int numOfPlayers;
	int winnerId; // -1 = No winner, x = playerId is the winner.

};