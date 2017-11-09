#include "GameStatus.h"

GameStatus::GameStatus()
{
}
GameStatus::GameStatus(Game* g)
{
	subject = g;
	subject->Register(this);
}

GameStatus::~GameStatus()
{
	subject->Unregister(this);
}
void GameStatus::Update() {
	display();
}
void GameStatus::display() {
	cout << "Players World Domination View" << endl << endl;
	for (unsigned int i = 0; i < subject->playerVector.size(); i++) {
		Player* currentPlayer = subject->playerVector[i];
		
		int percentageOfDomination = (int)((double)(((double)currentPlayer->getOwnedCountries().size()) / (double)(subject->loadedMap->getMap()->getContainedCountriesInMap().size())) * 100);
		string barGraph = "";

		for (unsigned int i = 0; i < percentageOfDomination; i++) {
			barGraph += "|";
		}

		cout << "Player #" << currentPlayer->getId() << "'s status: " << barGraph << endl;
		cout << percentageOfDomination << "% of World domination" << endl << endl;

	}
}
