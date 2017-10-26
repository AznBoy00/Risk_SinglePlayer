#include "Player.h"
#include "Dice.h"
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
	/*do {
		string attackingCountry;
		string attackTarget;

		cout << "Select which country is attacking." << endl; //player chooses which country is attacking.  
		cin >> attackingCountry;
		while (attackingCountry.getNumberOfTroops() < 2)
		{
			cout << "This country does not have enough armies to declare an attack. Choose another Country." << endl; // in case the player enters a country that does not have 2 armies
			cin >> attackingCountry;

		}if (attackingCountry.getNumberOfTroops() > 2) { // player selects which neighboring country he is attacking.
			cout << "Select which country " + attackingCountry + " is attacking." << endl;
			cin >> attackTarget;

			while (attackTargetisnotvalid)// checks if that country is a neighboring country. 
				cout << "You must choose a neighboring country" << endl;
			cin >> attackTarget;
		} if (attackTargetisvalid) {

			// this is where the dice function starts. 

			int dice1;
			int dice2;
			int maxDice1;
			int maxDice2;
			string siege;
			// calculate how many dice the attacking player is allowed to roll. 

			if (attackingCountry.getNumberOfTroops() > 3)
				maxDice1 = 3;
			else maxDice1 = attackingCountry.getNumberOfTroops() - 1;

			// calculate how many dice the defending player is allowed to roll. 

			if (attackedCountry.getNumberOfTroops < 2)
				maxDice2 = 1;
			else maxDice2 = 2;

			cout << "Choose the number of dice for the attacking country. 1 to " + maxDice1 << endl;

			cin >> dice1;
			while (dice1 <1 || dice1 >maxDice1) { // check if number of dice chosen is a valid number within the max number of dices allowed. 
				cout << "This is not a valid number of dice. Enter the number of dice for the attacking country." << endl;
				cin >> dice1;
			}

			cout << "choose the number of dice for the defending country. " << endl;
			cin >> dice2;
			while (dice2 <1 || dice2>maxDice2) {
				cout << "This is not a valid number of dice. Enter the number of dice for the defending country." << endl;
			}

			//rolling the dice 
			int dice1Results[3];
			int dice2Results[2];

			for (int i = 0; i < maxDice1; i++) {// attacker rolls the dice and puts results in the array, which then will be sorted from highest to lowest.
				dice1Results[i] = rollDiceOnce(); //randomly generate a number from 1 to 6 and store in the array. 
			}
			// sorting the results from the attack dice roll. 
			for (int i = 0; i < maxDice1 - 1; i++) {
				if (dice1Results[i] < dice1Results[i + 1]) {
					int temp;
					temp = dice1Results[i];
					dice1Results[i] = dice1Results[i + 1];
					dice1Results[i + 1] = temp;
				}
			}if (dice1Results[0] < dice1Results[1]) {
				int temp;
				temp = dice1Results[0];
				dice1Results[0] = dice1Results[1];
				dice1Results[1] = temp;
			}
			// sorting the results from the defence dice roll.
			if (dice2Results[0] < dice2Results[1]) {
				int temp;
				temp = dice2Results[0];
				dice2Results[0] = dice2Results[1];
				dice2Results[1] = temp;
			}
			//comparing the winner
			for (int i = 0; i < maxDice2; i++) {


			}

		}

	} while (attack == "yes");*/
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

	if (movingArmies < 0 || movingArmies > (ownedCountries[fromCountry - 1]->getNumberOfTroops() - 1)) {
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