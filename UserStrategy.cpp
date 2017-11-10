#include "UserStrategy.h"
#include "Time.h"
using namespace std;

class Strategy;

void UserStrategy::attack(Map* map, vector<Player*> playerVector) {
	char input;
	int atk, attackableCountries, atkSelection;
	Country *from, *target;

	player->stream << "\nATTACK PHASE!" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	do {
		cout << "Your countries:" << endl;
		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			cout << i + 1 << " - " << player->getOwnedCountries().at(i)->getNameOfCountry() << " | Army size: " << player->getOwnedCountries().at(i)->getNumberOfTroops() << endl;
		}

		cout << "Which country would you want to declare an attack with? (You must have at least 2 troops to be able to declare an attack)" << endl;
		cin >> atk;
		while (atk < 1 || atk > player->getOwnedCountries().size() || player->getOwnedCountries().at(atk - 1)->getNumberOfTroops() < 2) {
			cout << "Please enter a valid input (You must have at least 2 troops to be able to declare an attack):" << endl;
			cin >> atk;
		}
		cout << player->getOwnedCountries().size() + 1 << " - No Attack" << endl;
		from = player->getOwnedCountries().at(atk - 1);

		if (atk == player->getOwnedCountries().size() + 1) {
			break;
		}

		cout << "Which country do you want to attack?" << endl;
		for (size_t i = 0; i < from->getEnemies().size(); i++) {
			cout << i + 1 << " - " << from->getEnemies().at(i)->getNameOfCountry() << " | Army size: " << from->getEnemies().at(i)->getNumberOfTroops() << endl;
		}
		cin >> atkSelection;
		while (atkSelection < 1 || atkSelection > from->getEnemies().size()) {
			cout << "Please enter a valid input:" << endl;
			cin >> atkSelection;
		}
		target = from->getEnemies().at(atkSelection - 1);

		player->stream << "Player " << player->getId() << "'s country: " << from->getNameOfCountry() << " is attacking " << target->getNameOfCountry() << " belonging to Player " << target->getOwnerNumber() << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");

		attackDo(from, target, map, playerVector);

		cout << "Do you want to attack again? (y/n)" << endl;
		cin >> input;
		while (input != 'y' || input != 'n') {
			cout << "Please enter (y/n)." << endl;
			cin >> input;
		}
	} while (input != 'y');
}

void UserStrategy::attackDo(Country* atkFrom, Country* atkTarget, Map* map, vector<Player*> playerVector) {
	srand(time(0));
	int atkDiceRoll = (int)((3 * rand() / (RAND_MAX + 1.0)) + 1);
	int defDiceRoll = (int)((2 * rand() / (RAND_MAX + 1.0)) + 1);
	int atkRollValue = 0, defRollValue = 0;
	int temp;

	player->stream << "Attacker will roll " << atkDiceRoll << " dices and defender will roll " << defDiceRoll << " dices" << endl;

	// Sets dice roll.
	if (atkFrom->getNumberOfTroops() < atkDiceRoll) {
		atkDiceRoll = atkFrom->getNumberOfTroops() - 1;
	}
	if (atkTarget->getNumberOfTroops() < defDiceRoll) {
		defDiceRoll = atkTarget->getNumberOfTroops();
	}
	for (size_t i = 0; i < atkDiceRoll; i++) {
		atkRollValue += player->getDice().rollDiceOnce();
	}
	for (size_t i = 0; i < defDiceRoll; i++) {
		defRollValue += this->findTarget(playerVector, atkTarget)->getDice().rollDefenseDice(); //fix this
	}
	if (atkRollValue <= defRollValue) {
		player->stream << "Attacker lost the fight. (" << atkRollValue << " vs " << defRollValue << ")" << endl;
		player->stream << "Attacker has " << atkFrom->getNumberOfTroops() << " troops left." << endl;
		player->stream << "Defender has " << atkTarget->getNumberOfTroops() << " troops left." << endl;
		atkFrom->setNumberOfTroops(atkFrom->getNumberOfTroops() - 1);
	}
	else {
		player->stream << "Attacker won the fight. (" << atkRollValue << " vs " << defRollValue << ")" << endl;
		player->stream << "Attacker has " << atkFrom->getNumberOfTroops() << " troops left." << endl;
		player->stream << "Defender has " << atkTarget->getNumberOfTroops() << " troops left." << endl;
		atkTarget->setNumberOfTroops(atkTarget->getNumberOfTroops() - 1);
	}
	//Conquered territory process.
	if (atkTarget->getNumberOfTroops() == 0) {
		temp = atkFrom->getNumberOfTroops();
		atkTarget->setNumberOfTroops(temp - 1);
		atkFrom->setNumberOfTroops(1);
		atkTarget->setOwnerNumber(atkFrom->getOwnerNumber());

		player->stream << "Attacker has conquered " << atkTarget->getNameOfCountry() << endl;
		player->setConquered(true);
	}
	player->Notify();
	player->stream.clear();
	player->stream.str("");
}

Player* UserStrategy::findTarget(vector<Player*> playerVector, Country* atkTarget) {
	for (int i = 0; i < playerVector.size(); i++) {
		if (playerVector.at(i)->getId() == atkTarget->getOwnerNumber()) {
			return playerVector.at(i);
		}
	}
	cout << "Player not found, error! Program will exit." << endl;
	exit(1);
}

void UserStrategy::reinforce(Map* map, Deck* deck) {

	bool reinforceBool = false;
	string proceed;
	//removed srand(time(0));

	player->stream << "------------------------------------------\n"
		<< "IT'S PLAYER " << player->getId() << "'S TURN!\n"
		<< "Turn #: " << player->getTurnNumber() << "\n"
		<< "------------------------------------------\n"
		<< "Do you want to reinforce? (y/n)" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	cin >> proceed;
	
	if (proceed.compare("y") == 0) {
		reinforceBool = true;
	}
	else if (proceed.compare("n") == 0) {
		return;
	}
	else {
		player->stream << "Not a valid input." << endl;
	}
	if (reinforceBool) {

		unsigned int addArmies = 0;
		/*cout << "Enter number of armies to add. " << endl;// added input output.
		cin >> addArmies;*/
		addArmies += player->getOwnedCountries().size() < 12 ? 3 : (int)(player->getOwnedCountries().size() / 3);

		for (unsigned int i = 0; i < map->getContainedContinentsInMap().size(); i++) {
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

		player->stream << "We will be adding " << addArmies << " armies to Player " << player->getId() << "'s countries" << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");

		cout << "Here's a list of countries." << endl;
		for (unsigned int i = 0; i < player->getOwnedCountries().size(); i++) {
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


			player->stream << "Adding an army to " << player->getOwnedCountries()[country - 1]->getNameOfCountry() << endl;
			player->stream << player->getOwnedCountries()[country - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[country - 1]->getNumberOfTroops() << " armies." << endl;
			player->Notify();
			player->stream.clear();
			player->stream.str("");
		}
	}
}

void UserStrategy::fortify() {
	srand(time(0));
	player->stream << "FORTIFYING PHASE" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	cout << "Select a country which will have their armies moved by their respective number shown." << endl;
	for (unsigned int i = 0; i < player->getOwnedCountries().size(); i++) {
		cout << i + 1 << ": " << player->getOwnedCountries()[i]->getNameOfCountry() << " - " << player->getOwnedCountries()[i]->getNumberOfTroops() << " Armies." << endl;
	}
	unsigned int fromCountry, toCountry;

	cin >> fromCountry;
	while (fromCountry > player->getOwnedCountries().size() || fromCountry < 1) {
		cout << "Not a valid country number. Please enter a valid country number.";
		cin >> fromCountry;
	}

	cout << "Select a country to transfer those armies to." << endl;
	cin >> toCountry;
	while (toCountry > player->getOwnedCountries().size() || toCountry < 1) {
		cout << "Not a valid country number. Please enter a valid country number.";
		cin >> fromCountry;
	}
	player->stream << "Transferring from country: " << player->getOwnedCountries()[fromCountry-1]->getNameOfCountry() << " to " << player->getOwnedCountries()[toCountry-1]->getNameOfCountry() << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	cout << "Select the number of armies you want to move." << endl;
	int movingArmies;

	cin >> movingArmies;// added cin
	while (movingArmies < 0 || movingArmies >(player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() - 1)) {
		cout << "Invalid number of armies! Please enter a valid number of armies:" << endl;
		cin >> movingArmies;
	}

	player->stream << "Moving " << movingArmies << "armies" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	player->getOwnedCountries()[fromCountry - 1]->setNumberOfTroops(player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() - movingArmies);
	player->getOwnedCountries()[toCountry - 1]->setNumberOfTroops(player->getOwnedCountries()[toCountry - 1]->getNumberOfTroops() + movingArmies);

	player->stream << player->getOwnedCountries()[fromCountry - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() << " armies." << endl;
	player->stream << player->getOwnedCountries()[toCountry - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[toCountry - 1]->getNumberOfTroops() << " armies." << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");
}