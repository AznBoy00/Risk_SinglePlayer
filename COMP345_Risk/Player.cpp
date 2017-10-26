#include "Player.h"
#include "Dice.h"
#include <algorithm>

#include <iostream>
using namespace std;

Player::Player(int newId) {
	dice = new Dice();
	id = newId;
	cout << "\nDice object for player id: " << id << " created." << endl;//debug
	diceRolled = 0;
	diceDistribution[0] = 0;
	diceDistribution[1] = 0;
	diceDistribution[2] = 0;
	diceDistribution[3] = 0;
	diceDistribution[4] = 0;
	diceDistribution[5] = 0;
	cout << "Player id: " << id << " created." << endl;//debug
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

void Player::reinforce(Map map) {
	cout << "Player " << this->getId() << " is reinforcing." << endl;

	unsigned int addArmies = 0;

	addArmies += ownedCountries.size() < 12 ? 3 : (int)(ownedCountries.size() / 3);

	for (unsigned int i = 0; i < map.getContainedContinentsInMap().size(); i++) {
		if (includes(ownedCountries.begin(),
			ownedCountries.end(),
			map.getContainedContinentsInMap()[i]->getContainedCountriesInContinent().begin(),
			map.getContainedContinentsInMap()[i]->getContainedCountriesInContinent().end())) {
			addArmies += map.getContainedContinentsInMap()[i]->getContinentValue();
		}
	}

	//Need to add armies when exchange
	//Need help with this one

}

void Player::attack() {
	cout << "Player " << this->getId() << " is attacking." << endl;
}

void Player::fortify() {
	cout << "Player " << this->getId() << " is fortifying." << endl;

	cout << "Select a country which will have their armies moved by their respective number shown." << endl;
	for (unsigned int i = 0; i < ownedCountries.size(); i++) {
		cout << i + 1 << ": " << ownedCountries[i] << " - " << ownedCountries[i]->getNumberOfTroops() << "Armies." << endl;
	}
	unsigned int fromCountry, toCountry;
	cin >> fromCountry;
	cout << "Select a country to transfer those armies by their respective number shown." << endl;
	cin >> toCountry;

	if (fromCountry < 1 || fromCountry > ownedCountries.size()
		|| toCountry < 1 || toCountry > ownedCountries.size()) {
		cout << "Invalid countries!" << endl;
		exit(0);
	}

	cout << "Select a the number of armies you want to move." << endl;
	unsigned int movingArmies;
	cin >> movingArmies;

	if (movingArmies < 0 || movingArmies >(ownedCountries[fromCountry - 1]->getNumberOfTroops() - 1)) {
		cout << "Invalid number!" << endl;
		exit(0);
	}
	int ArmiesFrom = ownedCountries[fromCountry - 1]->getNumberOfTroops();
	int ArmiesTo = ownedCountries[toCountry - 1]->getNumberOfTroops();
	ownedCountries[fromCountry]->setNumberOfTroops(ArmiesFrom - movingArmies);
	ownedCountries[toCountry]->setNumberOfTroops(ArmiesTo + movingArmies);

}

void Player::setTurnNumber(int t) {
	turnNumber = t;
}

int Player::getTurnNumber() {
	return turnNumber;
}