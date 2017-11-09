#include <iostream>
#include "Player.h"
#include "MapLoader.h"

using namespace std;

class Game {
public:
	Game();
	void selectMap();
	vector<Player*> playerVector;
	vector<Player*> turnVector;
	MapLoader* loadedMap;
	void initializePlayers();
	void assignTurns();
	void assignCountries();
	void assignArmies();
private:
	int numOfPlayers;
	int winnerId; // -1 = No winner, x = playerId is the winner.
	void startGame();
};