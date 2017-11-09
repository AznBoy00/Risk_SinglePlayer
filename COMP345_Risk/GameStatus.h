#pragma once
#include "Observer.h"
#include "Game.h"
class GameStatus : public Observer
{
public:
	GameStatus();
	GameStatus(Game* g);
	~GameStatus();
	void Update();
	void display();
private:
	Game *subject;
};

