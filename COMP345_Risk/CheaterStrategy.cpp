#include "CheaterStrategy.h"
#include "Time.h"
using namespace std;

class Strategy;

void CheaterStrategy::attack(Map* map, vector<Player*> playerVector) {
	string input;
	int atk, atkSelection;
	Country *from = NULL;
	Country *target = NULL;

	player->stream << "\nATTACK PHASE" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	
	cout << "Cheater's countries:" << endl;
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		cout << i + 1 << " - " << player->getOwnedCountries().at(i)->getNameOfCountry() << " | Army size: " << player->getOwnedCountries().at(i)->getNumberOfTroops() << endl;
	}

	player->stream << "Player " << player->getId() << " is attacking all of its neighbor enemies." << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	attackDo(from, target, map, playerVector);

	if (player->getOwnedCountries().size() >= map->getContainedCountriesInMap().size()) {
		player->setWinner(true);
	}
}

void CheaterStrategy::attackDo(Country* atkFrom, Country* atkTarget, Map* map, vector<Player*> playerVector) {
	//srand(time(0));

	int temp, input;

	for (int i = 0; i < player->getOwnedCountries().size(); i++) {
		atkFrom = player->getOwnedCountries().at(i);
		for (int j = 0; j < atkFrom->getEnemies().size(); j++) {
			//fix duplicate conquering
			atkTarget = atkFrom->getEnemies().at(j);
			//Player* conqueredPlayer = findTarget(playerVector, atkTarget);
			Player* conqueredPlayer = playerVector[atkTarget->getOwnerNumber() - 1];
			for (int k = 0; k < conqueredPlayer->getOwnedCountries().size(); k++) {
				if (atkTarget->getNameOfCountry().compare(conqueredPlayer->getOwnedCountries().at(k)->getNameOfCountry()) == 0) {
					player->stream << "Attacker has conquered " << atkTarget->getNameOfCountry() << endl;
					atkTarget->setNumberOfTroops(1);
					atkTarget->setOwnerNumber(atkFrom->getOwnerNumber());
					player->setOwnedCountry(atkTarget);
					//player->stream << "Swapping " << conqueredPlayer->getOwnedCountries()[k]->getNameOfCountry() << " with " << conqueredPlayer->getOwnedCountries().back()->getNameOfCountry() << endl;
					swap(conqueredPlayer->getOwnedCountries() [k], conqueredPlayer->getOwnedCountries().back());
					//player->stream << "Erasing " << conqueredPlayer->getOwnedCountries().back()->getNameOfCountry() << " from " << conqueredPlayer->getId() << endl;
					conqueredPlayer->getOwnedCountries().pop_back();
					break;
				}
				}
			
		}
	}
	player->stream << "Attacker won the fight." << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");
	player->setConquered(true);
				
}
		


Player* CheaterStrategy::findTarget(vector<Player*> playerVector, Country* atkTarget) {
	for (int i = 0; i < playerVector.size(); i++) {
		if (playerVector.at(i)->getId() == atkTarget->getOwnerNumber()) {
			return playerVector.at(i);
		}
	}
	cout << "Player not found, error! Program will exit." << endl;
	exit(1);
}

void CheaterStrategy::reinforce(Map* map, Deck* deck) {
	int input;

	player->stream << "------------------------------------------\n"
		<< "IT'S PLAYER " << player->getId() << "'S TURN!\n"
		<< "Turn #: " << player->getTurnNumber() << "\n"
		<< "------------------------------------------\n";
	player->Notify();
	player->stream.clear();
	player->stream.str("");


	player->stream << "We will be doubling the armies to Player " << player->getId() << "'s countries as the turn starts." << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

		cout << "Your countries:" << endl;
		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			cout << i + 1 << " - " << player->getOwnedCountries().at(i)->getNameOfCountry() << " | Army size: " << player->getOwnedCountries().at(i)->getNumberOfTroops() << endl;
		}

		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			player->getOwnedCountries().at(i)->setNumberOfTroops(player->getOwnedCountries().at(i)->getNumberOfTroops() *2);
			player->stream << "Doubled armies to " << player->getOwnedCountries().at(i)->getNameOfCountry() << " belonging to Player " << player->getId() << endl;
			player->Notify();
			player->stream.clear();
			player->stream.str("");
		}

}

void CheaterStrategy::fortify() {

	player->stream << "FORTIFYING PHASE" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	for (unsigned int i = 0; i < player->getOwnedCountries().size(); i++) {
	 	if (player->getOwnedCountries().at(i)->getEnemies().size() > 0) {
			player->getOwnedCountries().at(i)->setNumberOfTroops(player->getOwnedCountries().at(i)->getNumberOfTroops() * 2);
			player->stream << player->getOwnedCountries().at(i)->getNameOfCountry() << " has " << player->getOwnedCountries().at(i)->getNumberOfTroops() << " armies." << endl;				
		}
	}
	player->stream << "Doubled armies on countries neighboring hostile countries." << endl;

	player->Notify();
	player->stream.clear();
	player->stream.str("");
}