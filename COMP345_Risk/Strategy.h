#pragma once
#include "Player.h"
#include <vector>

class Player;

class Strategy {
	public:
		Player* player;
		Strategy(Player* player);
		virtual void reinforce(Map* map, Deck* deck) = 0;
		virtual void attack(Map * map, std::vector<Player*> playerVector) = 0;
		virtual void fortify() = 0;
		
};