#include "UserStrategy.h"
#include "Time.h"
#include <exception>

class Strategy;

void UserStrategy::attack(Map* map, vector<Player*> playerVector) {
	int atk, attackableCountries, atkSelection;
	Country *from, *target;

	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		from = player->getOwnedCountries().at(i);
		if (player->getOwnedCountries().at(i)->getNumberOfTroops() >= 2) {
			attackableCountries = from->getEnemies().size();
			cout << "Select a country to attack:" << endl;
			for (size_t j = 0; j < attackableCountries; j++) {
				cout << j + 1 << ": " << from->getEnemies().at(j)->getNameOfCountry() << endl;
			}
			cin >> atkSelection;
			while (atkSelection < 1 || atkSelection > attackableCountries) {
				cout << "Not a valid selection. Please choose a country to attack.";
				cin >> atkSelection;
			}
			target = from->getEnemies().at(atkSelection - 1);
			cout << "Player " << player->getId() << "'s country: " << from->getNameOfCountry() << " is attacking " << target->getNameOfCountry() << " belonging to Player " << target->getOwnerNumber() << endl;
			attackDo(from, target, map, playerVector);
		}
	}
}

void UserStrategy::attackDo(Country* atkFrom, Country* atkTarget, Map* map, vector<Player*> playerVector) {
	srand(time(0));
	//find playerVector;player ID for atkFrom
	for (size_t i = 0; i < playerVector.size(); i++) {
		if (playerVector.at(i)->getId() == atkFrom->getOwnerNumber()) {

		}
	}
	int atkDiceRoll = (int)((3 * rand() / (RAND_MAX + 1.0)) + 1);
	int defDiceRoll = (int)((2 * rand() / (RAND_MAX + 1.0)) + 1);
	int atkRollValue = 0, defRollValue = 0;
	int temp;

	// Sets dice roll.
	if (atkFrom->getNumberOfTroops() < atkDiceRoll) {
		atkDiceRoll = atkFrom->getNumberOfTroops() - 1;
	}
	if (atkTarget->getNumberOfTroops() < defDiceRoll) {
		defDiceRoll = atkTarget->getNumberOfTroops();
	}

	cout << "Attacker will roll " << atkDiceRoll << " dices and defender will roll " << defDiceRoll << " dices" << endl;

	for (size_t i = 0; i < atkDiceRoll; i++) {
		atkRollValue += player->getDice().rollDiceOnce();
	}
	for (size_t i = 0; i < defDiceRoll; i++) {
		defRollValue += findTarget(playerVector, atkTarget)->getDice().rollDefenseDice();
	}
	if (atkRollValue <= defRollValue) {
		cout << "Attacker lost the fight. (" << atkRollValue << " vs " << defRollValue << ")" << endl;
		cout << "Attacker has " << atkFrom->getNumberOfTroops() << " troops left." << endl;
		cout << "Defender has " << atkTarget->getNumberOfTroops() << " troops left." << endl;
		atkFrom->setNumberOfTroops(atkFrom->getNumberOfTroops() - 1);
	}
	else {
		cout << "Attacker won the fight. (" << atkRollValue << " vs " << defRollValue << ")" << endl;
		cout << "Attacker has " << atkFrom->getNumberOfTroops() << " troops left." << endl;
		cout << "Defender has " << atkTarget->getNumberOfTroops() << " troops left." << endl;
		atkTarget->setNumberOfTroops(atkTarget->getNumberOfTroops() - 1);
	}
	//Conquered territory process.
	if (atkTarget->getNumberOfTroops() == 0) {
		temp = atkFrom->getNumberOfTroops();
		atkTarget->setNumberOfTroops(temp - 1);
		atkFrom->setNumberOfTroops(1);
		atkTarget->setOwnerNumber(atkFrom->getOwnerNumber());
		cout << "Attacker has conquered " << atkTarget->getNameOfCountry() << endl;
	}
}

Player* UserStrategy::findTarget(vector<Player*> playerVector, Country* atkTarget) {
	try {
		for (size_t i = 0; i < playerVector.size(); i++) {
			if (playerVector.at(i)->getId() == atkTarget->getOwnerNumber()) {
				return playerVector.at(i);
			}
		}
	} catch (exception e){
		cout << "Player not found, error! Program will exit." << endl;
		exit(1);
	}
}

void UserStrategy::reinforce(Map* map, Deck* deck) {
	//removed srand(time(0));
	cout << "Player " << player->getId() << " is reinforcing." << endl; // output.
	unsigned int addArmies = 0;
	/*cout << "Enter number of armies to add. " << endl;// added input output.
	cin >> addArmies;*/
	addArmies += player->getOwnedCountries().size() < 12 ? 3 : (int)(player->getOwnedCountries().size() / 3);

	for (size_t i = 0; i < map->getContainedContinentsInMap().size(); i++) {
		/*if (includes(ownedCountries.begin(),
		ownedCountries.end(),
		map->getContainedContinentsInMap()[i]->getContainedCountriesInContinent().begin(),
		map->getContainedContinentsInMap()[i]->getContainedCountriesInContinent().end())) {
		addArmies += map->getContainedContinentsInMap()[i]->getContinentValue();
		}*/
		addArmies += map->getContainedContinentsInMap()[i]->getContinentValue();
	}

	if (player->getHand()->cardsInHand(player->getId(), deck) > 5) {
		cout << "You have more than 5 cards in hand. You are forced to exchange." << endl;
		addArmies += player->getHand()->exchange(player->getId(), deck);
	}
	else {
		cout << "Try to exchange? (y/n)" << endl;
		string confirm;
		cin >> confirm;// removed hardcode.
		if (confirm == "y") {
			addArmies += player->getHand()->exchange(player->getId(), deck);
		}
		else if (confirm == "n") {
			return;
		}
		else {
			cout << "Not a proper input. Try to exchange? (y/n)";
			cin >> confirm;
		}
	}

	cout << "Here's a list of countries." << endl;
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		cout << i + 1 << ": " << player->getOwnedCountries()[i]->getNameOfCountry() << endl;
	}

	int country;

	while (addArmies != 0) {
		cout << addArmies << " armies remaining." << endl;
		cout << "Please select a country by their number above." << endl;

		cin >> country;
		while (country > player->getOwnedCountries().size() || country < 1) {
			cout << "Not a valid country number. Enter a valid number.";
			cin >> country;
		}

		player->getOwnedCountries()[country - 1]->setNumberOfTroops(player->getOwnedCountries()[country - 1]->getNumberOfTroops() + 1);
		addArmies--;

		cout << "Adding an army to " << player->getOwnedCountries()[country - 1]->getNameOfCountry() << endl;
		cout << player->getOwnedCountries()[country - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[country - 1]->getNumberOfTroops() << " armies." << endl;
	}
}

void UserStrategy::fortify() {
	srand(time(0));
	cout << "Player " << player->getId() << " is fortifying." << endl;

	cout << "Select a country which will have their armies moved by their respective number shown." << endl;
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		cout << i + 1 << ": " << player->getOwnedCountries()[i]->getNameOfCountry() << " - " << player->getOwnedCountries()[i]->getNumberOfTroops() << " Armies." << endl;
	}
	unsigned int fromCountry, toCountry;

	// removed fromCountry = (int)((ownedCountries.size() * rand() / (RAND_MAX + 1.0)));
	cin >> fromCountry;
	while (fromCountry > player->getOwnedCountries().size() || fromCountry < 1) {
		cout << "Not a valid country number. Please enter a valid country number.";
		cin >> fromCountry;
	}

	// removed toCountry = (int)((ownedCountries.size() * rand() / (RAND_MAX + 1.0)));
	cout << "Select a country to transfer those armies to." << endl;
	cin >> toCountry;
	while (toCountry > player->getOwnedCountries().size() || toCountry < 1) {
		cout << "Not a valid country number. Please enter a valid country number.";
		cin >> fromCountry;
	}
	cout << "Transferring from country: " << player->getOwnedCountries().at(fromCountry)->getNameOfCountry() << " to " << player->getOwnedCountries().at(toCountry)->getNameOfCountry() << endl;

	cout << "Select the number of armies you want to move." << endl;
	int movingArmies;

	cin >> movingArmies;// added cin
	while (movingArmies < 0 || movingArmies >(player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() - 1)) {
		cout << "Invalid number of armies! Please enter a valid number of armies:" << endl;
		cin >> movingArmies;
	}

	cout << "Moving " << movingArmies << "armies" << endl;

	player->getOwnedCountries()[fromCountry - 1]->setNumberOfTroops(player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() - movingArmies);
	player->getOwnedCountries()[toCountry - 1]->setNumberOfTroops(player->getOwnedCountries()[toCountry - 1]->getNumberOfTroops() + movingArmies);

	cout << player->getOwnedCountries()[fromCountry - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() << " armies." << endl;
	cout << player->getOwnedCountries()[toCountry - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[toCountry - 1]->getNumberOfTroops() << " armies." << endl;

}