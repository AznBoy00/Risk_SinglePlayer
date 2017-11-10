#pragma once
#include "Strategy.h"

class AggressiveStrategy : public Strategy
{
public:
	AggressiveStrategy(Player* user) : Strategy(user) {}
private:
	void attack(Map* map, vector<Player*> playerVector);
	void attackDo(Country* atkFrom, Country* atkTarget, Map* map, vector<Player*> playerVector);
	Player * findTarget(vector<Player*> playerVector, Country * atkTarget);
	void reinforce(Map* map, Deck* deck);
	void fortify();
};