#pragma once
#include "Observer.h"
#include "Game.h"

class TurnNumber : public Observer
{
public:
	TurnNumber();
	TurnNumber(Game* g);
	~TurnNumber();
	void Update();
	void display();
private:
	Game *subject;
};

