#include "PHODecorator.h"

void PHODecorator::Update() {
	display();
}
void PHODecorator::display() {
	cout << "====================================\n"
		<< "Player Hand Observer Decorator\n"
		<< "====================================" << endl;
	for (unsigned int i = 0; i < subject->playerVector.size(); i++) {
		Player* currentPlayer = subject->playerVector[i];
		subject->playDeck->showCardsInHand(currentPlayer->getId(), subject->playDeck);
	}


}

