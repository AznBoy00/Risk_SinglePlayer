#include "Dice.h"
#include "Player.h"
#include "Time.h"

#include <iostream>
using namespace std;

/*
Dice default constructor.
*/
Dice::Dice() {
	totalDiceRolled = 0;
	diceRollDistribution[0] = 0;
	diceRollDistribution[1] = 0;
	diceRollDistribution[2] = 0;
	diceRollDistribution[3] = 0;
	diceRollDistribution[4] = 0;
	diceRollDistribution[5] = 0;
	cout << "DICE.CPP::DICE OBJECT CREATED!" << endl;
	cout << "DICE.CPP::totalDiceRolled: " << totalDiceRolled << endl;
	for (size_t i = 0; i < 6; i++) {
		cout << "DICE.CPP::diceRollDistribution: " << i << ": " << diceRollDistribution[i] << endl;
	}
}

/*
Dice destructor.
*/
Dice::~Dice() {
}

/*
@param int num
rollDice method that will roll a dice x number of times depending on int num input.
*/
void Dice::rollDice(int num) {
	// Weird way to make rand() as random as possible.
	int r;
	for (size_t i = 0; i < num; i++) {
		r = rollDiceOnce();
		diceRollDistribution[r - 1] += 1;
		totalDiceRolled++;
		cout << "DICE.CPP::totalDiceRolled: " << totalDiceRolled << endl;
	}
	//debug
	for (size_t i = 0; i < 6; i++) {
		cout << "\nDICE.CPP::Number of " << i + 1 << " rolled: " << diceRollDistribution[i] << endl;
	}
}

int Dice::rollDiceOnce() {
	int r = (int)((6 * rand() / (RAND_MAX + 1.0)) + 1);
	cout << "DICE.CPP::Turn player rolled " << r << endl;
	return r;
}

void Dice::showStats() {
	double nominator;
	double denominator;
	cout << "\nDICE.CPP::Number of dice rolled: " << totalDiceRolled << endl;
	for (size_t i = 0; i < 6; i++) {
		nominator = diceRollDistribution[i];
		denominator = totalDiceRolled;
		cout << "DICE.CPP::Number of " << i + 1 << " rolled: " << (double)(nominator / denominator) * 100 << "%" << endl;
	}
}
