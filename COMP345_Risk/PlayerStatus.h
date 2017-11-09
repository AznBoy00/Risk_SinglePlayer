#pragma once
#include "Player.h";
#include "Observer.h"

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

