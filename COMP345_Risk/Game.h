#include <iostream>
#include "Player.h"
#include "Subject.h"
using namespace std;

class Game : public Subject {
public:
	Game();
	vector<Player*> playerVector;

private:
	int numOfPlayers;
	int winnerId; // -1 = No winner, x = playerId is the winner.
};