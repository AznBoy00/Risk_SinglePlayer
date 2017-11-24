#include "PlayerStatus.h"


PlayerStatus::PlayerStatus()
{
}

PlayerStatus::PlayerStatus(Player* p)
{
	subject = p;
	subject->Register(this);
}

PlayerStatus::~PlayerStatus()
{
	subject->Unregister(this);
}

void PlayerStatus::Update() {
	display();
}
void PlayerStatus::display() {
	cout << subject->getState();
}