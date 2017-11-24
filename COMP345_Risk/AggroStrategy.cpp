#include "AggroStrategy.h"
#include "Time.h"

class Strategy;

//Computer Aggro Strategy

void AggroStrategy::attack(Map* map, vector<Player*> playerVector) {
	string input;
	int atk = 1, atkSelection;
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
		Country* strongestCountry = player->getOwnedCountries().at(0);
		for (int i = 1; i < player->getOwnedCountries().size(); i++) {
			if (player->getOwnedCountries()[i]->getNumberOfTroops() > strongestCountry->getNumberOfTroops()) {
				strongestCountry = player->getOwnedCountries()[i];
				atk = i + 1;
			}
		}

		if (strongestCountry->getNumberOfTroops() < 2) {
			return;
		}

		from = player->getOwnedCountries().at(atk - 1);

		cout << "\nNeighbor enemy countrie(s): " << endl;
		for (size_t i = 0; i < from->getEnemies().size(); i++) {
			cout << i + 1 << " - " << from->getEnemies().at(i)->getNameOfCountry() << " | Army size: " << from->getEnemies().at(i)->getNumberOfTroops() << endl;
		}
		cout << from->getEnemies().size() + 1 << " - No Attack" << endl;
		cout << "Which country do you want to attack?" << endl;
		atkSelection = 1;

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

		if (from->getEnemies().size() == 0) {
			input = "n";
		}
		else {
			input = "y";
		}
	} while (input == "y");

	if (player->getOwnedCountries().size() >= map->getContainedCountriesInMap().size()) {
		player->setWinner(true);
	}
}

void AggroStrategy::attackDo(Country* atkFrom, Country* atkTarget, Map* map, vector<Player*> playerVector) {
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
	input = atkMax;
	while (input < 1 || input > atkMax) {
		cout << "Please enter a number between (1 - " << atkMax << ")" << endl;
		cin >> input;
	}
	atkDiceRoll = input;

	cout << "How many dice(s) does the DEFENDER want to roll? (1 - " << defMax << ")" << endl;
	input = 1;
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
		}
		else {
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
				input = 1;
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

Player* AggroStrategy::findTarget(vector<Player*> playerVector, Country* atkTarget) {
	for (int i = 0; i < playerVector.size(); i++) {
		if (playerVector.at(i)->getId() == atkTarget->getOwnerNumber()) {
			return playerVector.at(i);
		}
	}
	cout << "Player not found, error! Program will exit." << endl;
	exit(1);
}

void AggroStrategy::reinforce(Map* map, Deck* deck) {
	int reinforceAmount = 0;
	int strongestArmy = 0;

	player->stream << "------------------------------------------\n"
		<< "IT'S PLAYER " << player->getId() << "'S TURN!\n"
		<< "Turn #: " << player->getTurnNumber() << "\n"
		<< "------------------------------------------\n";
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	int addArmies = 0;
	addArmies += player->getOwnedCountries().size() < 12 ? 3 : (int)(player->getOwnedCountries().size() / 3);

	player->stream << "We will be adding " << addArmies << " armies to Player " << player->getId() << "'s STRONGEST countries as the turn starts." << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	//find strongest army
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		if (player->getOwnedCountries()[i]->getNumberOfTroops() > strongestArmy) {
			strongestArmy = player->getOwnedCountries()[i]->getNumberOfTroops();
		}
	}

	//reinforce strongest army
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		if (player->getOwnedCountries()[i]->getNumberOfTroops() == strongestArmy) {
			reinforceAmount = addArmies;
			player->getOwnedCountries().at(i)->setNumberOfTroops(player->getOwnedCountries().at(i)->getNumberOfTroops() + reinforceAmount);
			addArmies -= reinforceAmount;
			reinforceAmount = 0;
			player->stream << "Added " << reinforceAmount << " armies to " << player->getOwnedCountries().at(i)->getNameOfCountry() << " belonging to Player " << player->getId() << endl;
			player->Notify();
			player->stream.clear();
			player->stream.str("");
			break;
		}
	}

	if (player->getHand()->cardsInHand(player->getId(), deck) > 5) {
		cout << "You have more than 5 cards in hand. Trading you hands for reinforcement troops..." << endl;
		addArmies += deck->exchangeHand(player->getId(), deck);
	}
	else {
		cout << "Do you want to exchange your cards? (y to exchange, otherwise reinforce phase will be over)" << endl;
		string confirm;
		confirm = "y";

		if (confirm == "y") {
			addArmies += deck->exchangeHand(player->getId(), deck);
		}
	}

	if (addArmies != 0) {
		player->stream << "We will be adding " << addArmies << " armies to Player " << player->getId() << "'s countrie(s) of choice" << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");

		//find strongest army
		strongestArmy = 0;
		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			if (player->getOwnedCountries()[i]->getNumberOfTroops() > strongestArmy) {
				strongestArmy = player->getOwnedCountries()[i]->getNumberOfTroops();
			}
		}
		//reinforce strongest army
		for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
			if (player->getOwnedCountries()[i]->getNumberOfTroops() == strongestArmy) {
				player->getOwnedCountries().at(i)->setNumberOfTroops(player->getOwnedCountries().at(i)->getNumberOfTroops() + reinforceAmount);
				addArmies -= reinforceAmount;
				player->stream << "Added " << reinforceAmount << " armies to " << player->getOwnedCountries().at(i)->getNameOfCountry() << " belonging to Player " << player->getId() << endl;
				player->Notify();
				player->stream.clear();
				player->stream.str("");
				break;
			}
		}
	}
}
	

void AggroStrategy::fortify() {
	int fromCountry, toCountry, moveTroops;
	int strongestArmy, strongestAlly;

	player->stream << "FORTIFYING PHASE" << endl;
	player->Notify();
	player->stream.clear();
	player->stream.str("");

	//to
	strongestArmy = 0;
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		if (player->getOwnedCountries()[i]->getNumberOfTroops() > strongestArmy) {
			strongestArmy = player->getOwnedCountries()[i]->getNumberOfTroops();
		}
	}
	cout << "Strongest army: " << strongestArmy << endl;
	for (size_t i = 0; i < player->getOwnedCountries().size(); i++) {
		if (player->getOwnedCountries()[i]->getNumberOfTroops() == strongestArmy) {
			toCountry = i + 1;
		}
	}
	cout << "To Country: " << toCountry << endl;

	//from
	strongestAlly = 0;
	for (size_t i = 0; i < player->getOwnedCountries()[toCountry - 1]->getAllies().size(); i++) {
		if (player->getOwnedCountries().at(toCountry - 1)->getAllies().at(i)->getNumberOfTroops() > strongestAlly) {
			strongestAlly = player->getOwnedCountries()[toCountry - 1]->getAllies()[i]->getNumberOfTroops();
		}
	}
	cout << "Strongest ally: " << strongestAlly << endl;
	for (size_t i = 0; i < player->getOwnedCountries()[toCountry - 1]->getAllies().size(); i++) {
		if (player->getOwnedCountries().at(toCountry - 1)->getAllies().at(i)->getNumberOfTroops() == strongestAlly) {
			fromCountry = i + 1;
		}
	}
	cout << "From Country: " << fromCountry << endl;

	moveTroops = strongestAlly - 1;

	if (moveTroops == 0) {
		player->stream << "No nearby ally countries can reinforce the strongest country" << endl;
		player->Notify();
		player->stream.clear();
		player->stream.str("");
	} else {
		player->stream << "Transferring " << moveTroops << " troops from country: " << player->getOwnedCountries()[toCountry - 1]->getAllies()[fromCountry - 1]->getNameOfCountry() << " to " << player->getOwnedCountries()[toCountry - 1]->getNameOfCountry() << endl;
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
}