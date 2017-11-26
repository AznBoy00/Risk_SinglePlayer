#include "PDODecorator.h"

void PDODecorator::Update() {
	display();
}
void PDODecorator::display() {
	cout << "====================================\n" 
		<< "Player Domination Observer Decorator\n" 
		<< "====================================" << endl;
	for (unsigned int i = 0; i < subject->playerVector.size(); i++) {
		Player* currentPlayer = subject->playerVector[i];
		int percentageOfDomination = (int)((double)(((double)currentPlayer->getOwnedCountries().size()) / (double)(subject->loadedMap->getMap()->getContainedCountriesInMap().size())) * 100);
		cout << "Player " << currentPlayer->getId() << ": " << percentageOfDomination << "% of World domination" << endl << endl;
	}
}

