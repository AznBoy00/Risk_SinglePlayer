#include "CCODecorator.h"


void CCODecorator::Update() {
	display();
}
void CCODecorator::display() {
	cout << "====================================\n"
		<< "Continent Control Observer Decorator\n"
		<< "====================================" << endl;
	for (int i = 0; i < subject->loadedMap->getMap()->getContainedContinentsInMap().size(); i++) {
		cout << subject->loadedMap->getMap()->getContainedContinentsInMap()[i]->getNameOfContinent() << " is dominated by Player " << continentDomination(subject->loadedMap->getMap()->getContainedContinentsInMap()[i])->getId() << endl;
}
	
}

Player* CCODecorator::continentDomination(Continent *c) {
	static Player* dominatingPlayer = NULL;
	double dominationRatio = 0;

	for (int i = 0; i < subject->playerVector.size(); i++) {
		int ownedCountries = 0;
		for (int j = 0; j < subject->playerVector[i]->getOwnedCountries().size(); j++) {
			if (subject->playerVector[i]->getOwnedCountries()[j]->getContinent().compare(c->getNameOfContinent()) == 0) {
				ownedCountries++;
			}
		}

		if ((double) ownedCountries / c->getContainedCountriesInContinent().size() > dominationRatio) {
			dominationRatio = (double) ownedCountries / c->getContainedCountriesInContinent().size();
			dominatingPlayer = subject->playerVector[i];
		}
	}
	cout << dominatingPlayer->getId() << " with ratio " << dominationRatio << endl;

	return dominatingPlayer;

}