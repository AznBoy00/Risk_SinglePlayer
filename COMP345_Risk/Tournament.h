#pragma once
#include "Player.h"
#include "MapLoader.h"
#include "Subject.h"
#include "PlayerStatus.h"
#include "UserStrategy.h"
#include "AggroStrategy.h"
#include "PassiveStrategy.h"
#include "CheaterStrategy.h"
#include "RandomStrategy.h"

#include <string>
#include <dirent.h>

class Tournament {
public:
	Tournament();
private:
	MapLoader* map1;
	MapLoader* map2;
	MapLoader* map3;
	MapLoader* map4;
	MapLoader* map5;

	vector<Game*> map1Games;
	vector<Game*> map2Games;
	vector<Game*> map3Games;
	vector<Game*> map4Games;
	vector<Game*> map5Games;

	int MAP_MIN = 1;
	int MAP_MAX = 5;

	int GAME_MIN = 1;
	int GAME_MAX = 5;

	int PLAYER_MIN = 2;
	int PLAYER_MAX = 4;

	int TURN_MIN = 10;
	int TURN_MAX = 50;

	void start();
	string winners;

	int selectMap();
	MapLoader* selectMap(int input);
	void initializePlayers(int playerNumber);
	void assignStrategies(int playerNumber);

	vector<Player*> playerVector;
	vector<PlayerStatus*> playersStatus;
};

