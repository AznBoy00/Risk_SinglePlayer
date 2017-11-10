#pragma once
#include "Observer.h"
#include "Player.h"

class Player;

class PlayerStatus : public Observer
{
public:
	PlayerStatus();
	~PlayerStatus();
	PlayerStatus(Player* p);
	void Update();
	void display();
private:
	Player* subject;
};

