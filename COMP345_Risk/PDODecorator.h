#pragma once
#include "GameDecorator.h"

class PDODecorator : public GameDecorator {
protected:
	GameStatus *gameStatus;
public:
	PDODecorator(GameStatus* g, Game* game) : GameDecorator(g, game) {}
	void Update();
	void display();

};