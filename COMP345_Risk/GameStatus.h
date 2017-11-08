#pragma once
#include "Observer.h"
#include "Game.h"
#include "Map.h"
class GameStatus : public Observer
{
public:
	GameStatus();
	GameStatus(Game* g);
	~GameStatus();
	void Update(Map *map);
	void display(Map *map);
private:
	Game *subject;
};

