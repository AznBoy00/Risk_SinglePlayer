#pragma once
#include "Observer.h"
#include "Game.h"

class GameStatus : public Observer
{
public:
	GameStatus();
	GameStatus(Game* g);
	~GameStatus();

	virtual void Update();
	virtual void display();
protected:
	Game *subject;
};

