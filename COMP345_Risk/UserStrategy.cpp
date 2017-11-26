#include "UserStrategy.h"
#include "Time.h"
using namespace std;

class Strategy;

void UserStrategy::attack(Map* map, vector<Player*> playerVector) {
	string input;
	int atk, atkSelection;
	Country *from, *target;

	player->stream << "\nATTACK PHASE" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	do {
		cout << "Your countries:" << endl;
		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			cout << i + 1 << " - " << player->getOwnedCountries().at(i)->getNameOfCountry() << " | Army size: " << player->getOwnedCountries().at(i)->getNumberOfTroops() << endl;
		}
		cout << player->getOwnedCountries().size() + 1 << " - No Attack" << endl;
		cout << "Which country would you want to declare an attack with? (You must have at least 2 troops to be able to declare an attack)" << endl;
		cin >> atk;
		if (atk == player->getOwnedCountries().size() + 1) {
			break;
		}
		while (atk < 1 || atk > player->getOwnedCountries().size() || player->getOwnedCountries().at(atk - 1)->getNumberOfTroops() < 2) {
			cout << "Please enter a valid input (You must have at least 2 troops to be able to declare an attack):" << endl;
			cin >> atk;
		}
		from = player->getOwnedCountries().at(atk - 1);

		cout << "\nNeighbor enemy countrie(s): " << endl;
		for (size_t i = 0; i < from->getEnemies().size(); i++) {
			cout << i + 1 << " - " << from->getEnemies().at(i)->getNameOfCountry() << " | Army size: " << from->getEnemies().at(i)->getNumberOfTroops() << endl;
		}
		cout << from->getEnemies().size() + 1 << " - No Attack" << endl;
		cout << "Which country do you want to attack?" << endl;
		cin >> atkSelection;

		while (atkSelection < 1 || atkSelection > from->getEnemies().size() + 1) {
			cout << "Please enter a valid input:" << endl;
			cin >> atkSelection;
		}

		if (atkSelection != from->getEnemies().size() + 1) {
			target = from->getEnemies().at(atkSelection - 1);

			player->stream << "Player " << player->getId() << "'s country: " << from->getNameOfCountry() << " is attacking " << target->getNameOfCountry() << " belonging to Player " << target->getOwnerNumber() << endl;
			player->Notify();
			player->stream.clear();
			player->stream.str("");

			attackDo(from, target, map, playerVector);
		}

		cout << "Do you want to attack again? (y to attack again, anything else will exit)" << endl;
		cin >> input;
	} while (input == "y");

	if (player->getOwnedCountries().size() >= map->getContainedCountriesInMap().size()) {
		player->setWinner(true);
	}
}

void UserStrategy::attackDo(Country* atkFrom, Country* atkTarget, Map* map, vector<Player*> playerVector) {
	//srand(time(0));
	int atkMax = atkFrom->getNumberOfTroops() - 1;
	int defMax = atkTarget->getNumberOfTroops();
	int atkRollValue, defRollValue;
	int execNumber, temp, input, atkDiceRoll, defDiceRoll;

	if (atkMax > 3) {
		atkMax = 3;
	}
	if (defMax > 2) {
		defMax = 2;
	}

	//Set dice roll(s) number
	cout << "How many dice(s) does the ATTACKER want to roll? (1 - " << atkMax << ")" << endl;
	cin >> input;
	while (input < 1 || input > atkMax) {
		cout << "Please enter a number between (1 - " << atkMax << ")" << endl;
		cin >> input;
	}
	atkDiceRoll = input;

	cout << "How many dice(s) does the DEFENDER want to roll? (1 - " << defMax << ")" << endl;
	cin >> input;
	while (input < 1 || input > defMax) {
		cout << "Please enter a number between (1 - " << defMax << ")" << endl;
		cin >> input;
	}
	defDiceRoll = input;

	player->stream << "Attacker will roll " << atkDiceRoll << " dices and defender will roll " << defDiceRoll << " dices" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");
	if (atkDiceRoll > defDiceRoll) {
		execNumber = atkDiceRoll;
	}
	else {
		execNumber = defDiceRoll;
	}
	cout << execNumber;
	for (size_t i = 0; i < execNumber; i++) {
		atkRollValue = player->getDice().rollDiceOnce();
		defRollValue = this->findTarget(playerVector, atkTarget)->getDice().rollDiceOnce();
		if (i + 1 > defDiceRoll) {
			defRollValue = 0;
		}
		if (atkRollValue <= defRollValue) {
			player->stream << "Attacker lost the fight. (" << atkRollValue << " vs " << defRollValue << ")" << endl;
			atkFrom->setNumberOfTroops(atkFrom->getNumberOfTroops() - 1);
			player->stream << "Attacker has " << atkFrom->getNumberOfTroops() << " troops left." << endl;
			player->stream << "Defender has " << atkTarget->getNumberOfTroops() << " troops left." << endl;
			player->Notify();
			player->stream.clear();
			player->stream.str("");
		} else {
			player->stream << "Attacker won the fight. (" << atkRollValue << " vs " << defRollValue << ")" << endl;
			atkTarget->setNumberOfTroops(atkTarget->getNumberOfTroops() - 1);
			player->stream << "Attacker has " << atkFrom->getNumberOfTroops() << " troops left." << endl;
			player->stream << "Defender has " << atkTarget->getNumberOfTroops() << " troops left." << endl;
			player->Notify();
			player->stream.clear();
			player->stream.str("");
			if (atkTarget->getNumberOfTroops() == 0) {
				player->stream << "Attacker has conquered " << atkTarget->getNameOfCountry() << endl;
				player->Notify();
				cout << "You have " << atkFrom->getNumberOfTroops() << " troops left in " << atkFrom->getNameOfCountry() << endl;
				cout << "How many troops do you want to move to " << atkTarget->getNameOfCountry() << "? (Maximum " << atkFrom->getNumberOfTroops() - 1 << ")" << endl;
				cin >> input;
				while (input < 0 || input > atkFrom->getNumberOfTroops() - 1) {
					cout << "Enter a valid input" << endl;
					cin >> input;
				}
				temp = atkFrom->getNumberOfTroops();
				atkTarget->setNumberOfTroops(input);
				atkFrom->setNumberOfTroops(temp - input);
				atkTarget->setOwnerNumber(atkFrom->getOwnerNumber());
				player->setOwnedCountry(atkTarget);
				Player* conqueredPlayer = findTarget(playerVector, atkTarget);
				for (size_t i = 0; i < conqueredPlayer->getOwnedCountries().size(); i++) {
					if (atkTarget->getNameOfCountry().compare(conqueredPlayer->getOwnedCountries().at(i)->getNameOfCountry()) == 0) {
						swap(conqueredPlayer->getOwnedCountries()[i], conqueredPlayer->getOwnedCountries().back());
						conqueredPlayer->getOwnedCountries().pop_back();
					}
				}
				player->setConquered(true);
				break;
			}
		}
	}
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
	int input, reinforceAmount;

	player->stream << "------------------------------------------\n"
		<< "IT'S PLAYER " << player->getId() << "'S TURN!\n"
		<< "Turn #: " << player->getTurnNumber() << "\n"
		<< "------------------------------------------\n";
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	int addArmies = 0;
	addArmies += player->getOwnedCountries().size() < 12 ? 3 : (int)(player->getOwnedCountries().size() / 3);

	player->stream << "We will be adding " << addArmies << " armies to Player " << player->getId() << "'s countries as the turn starts." << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	do {
		cout << "Your countries:" << endl;
		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			cout << i + 1 << " - " << player->getOwnedCountries().at(i)->getNameOfCountry() << " | Army size: " << player->getOwnedCountries().at(i)->getNumberOfTroops() << endl;
		}
		cout << "You have " << addArmies << " new troops that you can reinforce! Which country do you want to reinforce?" << endl;
		cin >> input;
		while (input < 1 || input > player->getOwnedCountries().size()) {
			cout << "Please enter a valid input:" << endl;
			cin >> input;
		}

		cout << "How many troops do you want to reinforce in " << player->getOwnedCountries().at(input - 1)->getNameOfCountry() << "?" << endl;
		cin >> reinforceAmount;
		while (reinforceAmount < 0 || reinforceAmount > addArmies) {
			cout << "Please enter a valid input:" << endl;
			cin >> reinforceAmount;
		}
		player->getOwnedCountries().at(input - 1)->setNumberOfTroops(player->getOwnedCountries().at(input - 1)->getNumberOfTroops() + reinforceAmount);
		addArmies -= reinforceAmount;
		player->stream << "Added " << reinforceAmount << " armies to " << player->getOwnedCountries().at(input - 1)->getNameOfCountry() << " belonging to Player " << player->getId() << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");
	} while (addArmies != 0);


	if (player->getHand()->cardsInHand(player->getId(), deck) > 5) {
		cout << "You have more than 5 cards in hand. Trading you hands for reinforcement troops..." << endl;
		addArmies += deck->exchangeHand(player->getId(), deck);
	} else {
		cout << "Do you want to exchange your cards? (y to exchange, otherwise reinforce phase will be over)" << endl;
		string confirm;
		cin >> confirm;

		if (confirm == "y") {
			addArmies += deck->exchangeHand(player->getId(), deck);
		}
	}

	if (addArmies != 0) {
		player->stream << "We will be adding " << addArmies << " armies to Player " << player->getId() << "'s countrie(s) of choice" << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");

		do {
			cout << "Your countries:" << endl;
			for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
				cout << i + 1 << " - " << player->getOwnedCountries().at(i)->getNameOfCountry() << " | Army size: " << player->getOwnedCountries().at(i)->getNumberOfTroops() << endl;
			}
			cout << "You have " << addArmies << " new troops that you can reinforce using your exchanged cards! Which country do you want to reinforce?" << endl;
			cin >> input;
			while (input < 1 || input > player->getOwnedCountries().size()) {
				cout << "Please enter a valid input:" << endl;
				cin >> input;
			}

			cout << "How many troops do you want to reinforce in " << player->getOwnedCountries().at(input - 1)->getNameOfCountry() << "?" << endl;
			cin >> reinforceAmount;
			while (reinforceAmount < 0 || reinforceAmount > addArmies) {
				cout << "Please enter a valid input:" << endl;
				cin >> reinforceAmount;
			}
			player->getOwnedCountries().at(input - 1)->setNumberOfTroops(player->getOwnedCountries().at(input - 1)->getNumberOfTroops() + reinforceAmount);
			addArmies -= reinforceAmount;
			player->stream << "Added " << reinforceAmount << " armies to " << player->getOwnedCountries().at(input - 1)->getNameOfCountry() << " belonging to Player " << player->getId() << endl;
			player->Notify();
			player->stream.clear();
			player->stream.str("");
		} while (addArmies != 0);
	}
}

void UserStrategy::fortify() {
	int fromCountry, toCountry, moveTroops;

	player->stream << "FORTIFYING PHASE" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	for (unsigned int i = 0; i < player->getOwnedCountries().size(); i++) {
		cout << i + 1 << ": " << player->getOwnedCountries()[i]->getNameOfCountry() << " | Army:" << player->getOwnedCountries()[i]->getNumberOfTroops() << endl;
		cout << "\tNeighbor ally:" << endl;
		for (unsigned int j = 0; j < player->getOwnedCountries()[i]->getAllies().size(); j++) {
			cout << "\t\t" << j + 1 << ": " << player->getOwnedCountries()[i]->getAllies()[j]->getNameOfCountry() << " | Army:" << player->getOwnedCountries()[i]->getNumberOfTroops() << endl;
		}
	}
	cout << "Select a country which will have their armies moved by their respective number shown. (Country must have more than 1 troop with at least an allied neighbor)" << endl;

	//from
	cin >> fromCountry;
	while (fromCountry > player->getOwnedCountries().size() || fromCountry < 1 || player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() < 2 || player->getOwnedCountries()[fromCountry - 1]->getAllies().size() == 0) {
		cout << "Not a valid country number. Please enter a valid country number.";
		cin >> fromCountry;
	}

	//to
	for (unsigned int i = 0; i < player->getOwnedCountries()[fromCountry - 1]->getAllies().size(); i++) {
		cout << i + 1 << ": " << player->getOwnedCountries()[fromCountry - 1]->getAllies()[i]->getNameOfCountry() << " | Army:" << player->getOwnedCountries()[i]->getNumberOfTroops() << endl;
	}
	cout << "Select a country to transfer those armies to." << endl;
	cin >> toCountry;
	while (toCountry > player->getOwnedCountries()[fromCountry - 1]->getAllies().size() || toCountry < 1) {
		cout << "Not a valid country number. Please enter a valid country number.";
		cin >> toCountry;
	}

	//#ofTroops
	cout << "How many troops do you want to transfer? (You have to leave at least 1 troop behind)" << endl;
	cin >> moveTroops;
	while (moveTroops > player->getOwnedCountries().at(fromCountry - 1)->getNumberOfTroops() - 1 || toCountry < 0) {
		cout << "Not a valid country number. Please enter a valid troop number.";
		cin >> moveTroops;
	}

	player->stream << "Transferring " << moveTroops << " troops from country: " << player->getOwnedCountries()[fromCountry - 1]->getNameOfCountry() << " to " << player->getOwnedCountries()[toCountry - 1]->getNameOfCountry() << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	player->getOwnedCountries()[fromCountry - 1]->setNumberOfTroops(player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() - moveTroops);
	player->getOwnedCountries()[toCountry - 1]->setNumberOfTroops(player->getOwnedCountries()[toCountry - 1]->getNumberOfTroops() + moveTroops);

	player->stream << player->getOwnedCountries()[fromCountry - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[fromCountry - 1]->getNumberOfTroops() << " armies." << endl;
	player->stream << player->getOwnedCountries()[toCountry - 1]->getNameOfCountry() << " has " << player->getOwnedCountries()[toCountry - 1]->getNumberOfTroops() << " armies." << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");
}