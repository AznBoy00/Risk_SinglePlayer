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
void GameStatus::Update(Map *map) {
	display(map);
}
void GameStatus::display(Map *map) {
	cout << "Players World Domination View" << endl;
	cout << "Each '=' is equal to 5%" << endl;
	for (unsigned int i = 0; subject->playerVector.size(); i++) {
		Player* currentPlayer = subject->playerVector[0];

		int percentageOfDomination = (int)(currentPlayer->getOwnedCountries().size()) / (map->getContainedCountriesInMap().size()) * 100;
		string barGraph = "";

		for (unsigned int i = 0; percentageOfDomination/5; i++) {
			barGraph += "=";
		}

		cout << "Player #" << currentPlayer->getId() << "'s status: " << barGraph << endl;
		cout << percentageOfDomination << "% of World domination" << endl;

	}
}
