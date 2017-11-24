#include "TurnNumber.h"

TurnNumber::TurnNumber()
{
}
TurnNumber::TurnNumber(Game* g)
{
	subject = g;
	subject->Register(this);
}

TurnNumber::~TurnNumber()
{
	subject->Unregister(this);
}
void TurnNumber::Update() {
	display();
}
void TurnNumber::display() {
	cout << "Turn Number: " << subject->turnCounter << endl;
	
}
