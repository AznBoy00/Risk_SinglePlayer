#include "Dice.h"
#include "Player.h"
#include "Time.h"

#include <iostream>
using namespace std;

/*
	Dice default constructor.
*/
Dice::Dice() {
	diceRollDistribution[0] = 0;
	diceRollDistribution[1] = 0;
	diceRollDistribution[2] = 0;
	diceRollDistribution[3] = 0;
	diceRollDistribution[4] = 0;
	diceRollDistribution[5] = 0;
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
	int r = (int)((6 * rand() / (RAND_MAX + 1.0)) + 1);
	int rr;
	for (size_t i = 0; i < num; i++) {
		rr = r;
		r = (int)((6 * rand() / (RAND_MAX + 1.0)) + 1);
		cout << "Roll #" << i+1 << ": " << r << endl;
		diceRollDistribution[r-1] += 1;
		//totalDiceRolled++;
	}
	//debug
	for (size_t i = 0; i < 6; i++) {
		cout << "Number of " << i+1 << " rolled: " << diceRollDistribution[i] << endl;
	}
}

int Dice::rollDiceOnce() {
	int r = (int)((6 * rand() / (RAND_MAX + 1.0)) + 1);
	cout << "Turn player rolled " << r << endl;
	return r;
}
