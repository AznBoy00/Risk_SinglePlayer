#include <iostream>
#include "Player.h"
using namespace std;

class Game {
public:
	Game();
	vector<Player*> playerVector;
	vector<Player*> turnVector;

private:
	int numOfPlayers;
	int winnerId; // -1 = No winner, x = playerId is the winner.
};