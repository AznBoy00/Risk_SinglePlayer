#include <iostream>
#include "Player.h"
using namespace std;

class Game {
public:
	Game();
	vector<Player*> playerVector;

private:
	int numOfPlayers;

};