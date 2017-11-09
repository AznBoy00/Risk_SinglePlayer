#include "Player.h"
#include "Dice.h"
#include "Time.h"
#include <algorithm>
#include <iostream>
using namespace std;

Player::Player(int newId) {
	dice = new Dice();
	id = newId;
	//cout << "\nDice object for player id: " << id << " created." << endl;//debug
	diceRolled = 0;
	diceDistribution[0] = 0;
	diceDistribution[1] = 0;
	diceDistribution[2] = 0;
	diceDistribution[3] = 0;
	diceDistribution[4] = 0;
	diceDistribution[5] = 0;
	cout << "Player id: " << id << " created." << endl; //debug
}

Player::~Player() {
}

Dice Player::getDice() {
	return *dice;
}

int Player::getId() {
	return id;
}

void Player::setId(int newId) {
	id = newId;
}

int Player::getDiceRolled() {
	return diceRolled;
}

void Player::setDiceRolled(int dice) {
	diceRolled = dice;
}

void Player::showStats() {
	double nominator;
	double denominator;
	cout << "\nPlayer ID: " << getId() << endl;
	cout << "Player hand: " << endl;
	//insert player hand object description here
	cout << "Number of dice rolled: " << diceRolled << endl;
	for (size_t i = 0; i < 6; i++) {
		nominator = diceDistribution[i];
		denominator = diceRolled;
		cout << "Number of " << i + 1 << " rolled: " << (double)(nominator / denominator) * 100 << "%" << endl;
	}
}

void Player::roll(int num) {
	int result;
	this->dice->rollDice(num);
	for (size_t i = 0; i < num; i++) {
		result = this->dice->rollDiceOnce();
		//result = (int)((6 * rand() / (RAND_MAX + 1.0)) + 1);
		//cout << "Player rolled: " << result << endl;
		this->diceDistribution[result - 1] += 1;
	}
	this->diceRolled += num;
}

void Player::reinforce(Map* map, Deck* deck) {
	//removed srand(time(0));
	cout << "Player " << this->getId() << " is reinforcing." << endl; // output.
	unsigned int addArmies = 0;
	/*cout << "Enter number of armies to add. " << endl;// added input output.
	cin >> addArmies;*/
	addArmies += ownedCountries.size() < 12 ? 3 : (int)(ownedCountries.size() / 3);

	for (unsigned int i = 0; i < map->getContainedContinentsInMap().size(); i++) {
		/*if (includes(ownedCountries.begin(),
		ownedCountries.end(),
		map->getContainedContinentsInMap()[i]->getContainedCountriesInContinent().begin(),
		map->getContainedContinentsInMap()[i]->getContainedCountriesInContinent().end())) {
		addArmies += map->getContainedContinentsInMap()[i]->getContinentValue();
		}*/
		addArmies += map->getContainedContinentsInMap()[i]->getContinentValue();
	}

	if (hand->cardsInHand(this->id, deck) > 5) {
		cout << "You have more than 5 cards in hand. You are forced to exchange." << endl;
		addArmies += hand->exchange(this->id, deck);
	} else {
		cout << "Try to exchange? (y/n)" << endl;
		string confirm;
		cin >> confirm;// removed hardcode.
		if (confirm == "y") {
			addArmies += hand->exchange(this->id, deck);
		} else if (confirm == "n") {
			return;
		} else {
			cout << "Not a proper input. Try to exchange? (y/n)";
			cin >> confirm;
		}
	}

	cout << "Here's a list of countries." << endl;
	for (unsigned int i = 0; i < ownedCountries.size(); i++) {
		cout << i + 1 << ": " << ownedCountries[i]->getNameOfCountry() << endl;
	}

	int country;

	while (addArmies != 0) {
		cout << addArmies << " armies remaining." << endl;
		cout << "Please select a country by their number above." << endl;

		cin >> country;
		while(country > ownedCountries.size() || country < 1){
			cout << "Not a valid country number. Enter a valid number.";
			cin >> country;
		}

		ownedCountries[country - 1]->setNumberOfTroops(ownedCountries[country - 1]->getNumberOfTroops() + 1);
		addArmies--;

		cout << "Adding an army to " << ownedCountries[country - 1]->getNameOfCountry() << endl;
		cout << ownedCountries[country - 1]->getNameOfCountry() << " has " << ownedCountries[country - 1]->getNumberOfTroops() << " armies." << endl;
	}
}

Player*::Player::findTarget(vector<Player*> playerVector, Country* atkTarget) {
	for (int i = 0; i < playerVector.size(); i++) {
		if (playerVector.at(i)->getId() == atkTarget->getOwnerNumber()) {
			return playerVector.at(i);
		}
	}
	cout << "Player not found, error! Program will exit." << endl;
	exit(1);
}

void::Player::attackDo(Country* atkFrom, Country* atkTarget, Map* map, vector<Player*> playerVector) {
	srand(time(0));
	int atkDiceRoll = (int)((3 * rand() / (RAND_MAX + 1.0)) + 1);
	int defDiceRoll = (int)((2 * rand() / (RAND_MAX + 1.0)) + 1);
	int atkRollValue = 0, defRollValue = 0;
	int temp;

	cout << "Attacker will roll " << atkDiceRoll << " dices and defender will roll " << defDiceRoll << " dices" << endl;

	// Sets dice roll.
	if (atkFrom->getNumberOfTroops() < atkDiceRoll) {
		atkDiceRoll = atkFrom->getNumberOfTroops() - 1;
	}
	if (atkTarget->getNumberOfTroops() < defDiceRoll) {
		defDiceRoll = atkTarget->getNumberOfTroops();
	}
	for (size_t i = 0; i < atkDiceRoll; i++) {
		atkRollValue += this->getDice().rollDiceOnce();
	}
	for (size_t i = 0; i < defDiceRoll; i++) {
		defRollValue += this->findTarget(playerVector, atkTarget)->getDice().rollDefenseDice(); //fix this
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

void Player::attack(Map* map, vector<Player*> playerVector) {
	int atk, attackableCountries, atkSelection;
	Country *from, *target;

	for (int i = 0; i < this->ownedCountries.size(); i++) {
		from = this->getOwnedCountries().at(i);
		if (this->getOwnedCountries().at(i)->getNumberOfTroops() >= 2) {
			attackableCountries = from->getEnemies().size();
			cout << "Select a country to attack:" << endl;
			for (int j = 0; j < attackableCountries; j++) {
				cout << j + 1 << ": " << from->getEnemies().at(j)->getNameOfCountry() << endl;
			}
			cin >> atkSelection;
			while (atkSelection < 1 || atkSelection > attackableCountries) {
				cout << "Not a valid selection. Please choose a country to attack.";
				cin >> atkSelection;
			}
			target = from->getEnemies().at(atkSelection-1);
			cout << "Player " << this->getId() << "'s country: " << from->getNameOfCountry() << " is attacking " << target->getNameOfCountry() << " belonging to Player " << target->getOwnerNumber() << endl;
			attackDo(from, target, map, playerVector);
		}
	}
}

void Player::fortify() {
	srand(time(0));
	cout << "Player " << this->getId() << " is fortifying." << endl;

	cout << "Select a country which will have their armies moved by their respective number shown." << endl;
	for (unsigned int i = 0; i < ownedCountries.size(); i++) {
		cout << i + 1 << ": " << ownedCountries[i]->getNameOfCountry() << " - " << ownedCountries[i]->getNumberOfTroops() << " Armies." << endl;
	}
	unsigned int fromCountry, toCountry;

	// removed fromCountry = (int)((ownedCountries.size() * rand() / (RAND_MAX + 1.0)));
	cin >> fromCountry;
	while (fromCountry > ownedCountries.size() || fromCountry < 1) {
		cout << "Not a valid country number. Please enter a valid country number.";
		cin >> fromCountry;
	}

	// removed toCountry = (int)((ownedCountries.size() * rand() / (RAND_MAX + 1.0)));
	cout << "Select a country to transfer those armies to." << endl;
	cin >> toCountry;
	while (toCountry > ownedCountries.size() || toCountry < 1) {
		cout << "Not a valid country number. Please enter a valid country number.";
		cin >> fromCountry;
	}
	cout << "Transferring from country: " << ownedCountries.at(fromCountry)->getNameOfCountry() << " to " << ownedCountries.at(toCountry)->getNameOfCountry() << endl;

	cout << "Select the number of armies you want to move." << endl;
	int movingArmies;
  
	cin >> movingArmies;// added cin
	while (movingArmies < 0 || movingArmies >(ownedCountries[fromCountry - 1]->getNumberOfTroops() - 1)) {
		cout << "Invalid number of armies! Please enter a valid number of armies:" << endl;
		cin >> movingArmies;
	}
  
	cout << "Moving " << movingArmies << "armies" << endl;

	ownedCountries[fromCountry - 1]->setNumberOfTroops(ownedCountries[fromCountry - 1]->getNumberOfTroops() - movingArmies);
	ownedCountries[toCountry - 1]->setNumberOfTroops(ownedCountries[toCountry - 1]->getNumberOfTroops() + movingArmies);

	cout << ownedCountries[fromCountry - 1]->getNameOfCountry() << " has " << ownedCountries[fromCountry - 1]->getNumberOfTroops() << " armies." << endl;
	cout << ownedCountries[toCountry - 1]->getNameOfCountry() << " has " << ownedCountries[toCountry - 1]->getNumberOfTroops() << " armies." << endl;
}

void Player::setTurnNumber(int t) {
	turnNumber = t;
}

int Player::getTurnNumber() {
	return turnNumber;
}