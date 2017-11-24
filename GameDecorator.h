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
		cout << "calling update from gamedecorator" << endl;
	}
	
	void display() {
		GameStatus::display();
	}
};