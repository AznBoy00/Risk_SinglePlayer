#pragma once
#include "GameStatus.h"

class GameDecorator : public GameStatus {
protected:
	GameStatus *gameStatus;

public:
	GameDecorator(GameStatus* g, Game* game) : GameStatus(game){
		this->gameStatus = g;
	}
	
	void Update() {
		GameStatus::Update();
	}
	
	void display() {
		GameStatus::display();
	}
};