#pragma once
#include "GameDecorator.h"

class PHODecorator : public GameDecorator {
protected:
	GameStatus *gameStatus;
public:
	PHODecorator(GameStatus* g, Game* game) : GameDecorator(g, game) {}
	void Update();
	void display();

};