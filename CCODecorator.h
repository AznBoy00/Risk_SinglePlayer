#pragma once
#include "GameDecorator.h"

class CCODecorator: public GameDecorator {
protected:
	GameStatus *gameStatus;
public:
	CCODecorator(GameStatus* g, Game* game) : GameDecorator(g, game) {}
	void Update();
	void display();
	Player* continentDomination(Continent* p);

};