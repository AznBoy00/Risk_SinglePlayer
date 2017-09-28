#include "Dice.h"
#include "Player.h"
#include "Time.h"

#include <iostream>
using namespace std;

/*
	Dice default constructor.
*/
Dice::Dice() {
	diceRollNumber = 0;
	totalDiceRolled = 0;
	diceRollDistribution[0] = 0;
	diceRollDistribution[1] = 0;
	diceRollDistribution[2] = 0;
	diceRollDistribution[3] = 0;
	diceRollDistribution[4] = 0;
	diceRollDistribution[5] = 0;
}

/*
	Dice constructor.
*/
/*Dice::Dice(int num) {
	diceRollNumber = num;
	totalDiceRolled = 0;
	diceRollDistribution[0] = 0;
	diceRollDistribution[1] = 0;
	diceRollDistribution[2] = 0;
	diceRollDistribution[3] = 0;
	diceRollDistribution[4] = 0;
	diceRollDistribution[5] = 0;
}*/

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
		totalDiceRolled++;
		//Debug purpose
		cout << "diceRollDistribution:\t" <<
		diceRollDistribution[0] << diceRollDistribution[1] << diceRollDistribution[2] << diceRollDistribution[3] << diceRollDistribution[4] << diceRollDistribution[5] << endl;
	}
}

/*
	diceRollNumber getter method.
*/
int Dice::getDiceRollNumber() {
	return diceRollNumber;
}

/*
	@param int num
	Setter method for diceRollNumber.
*/
void Dice::setDiceRollNumber(int num) {
	diceRollNumber = num;
}

//Debugging driver
/*int main() {
	srand(time(0));
	int num;
	cout << "How many dice(s) do you want to roll? (1-3)" << endl;
	cin >> num;
	while (num < 1 || num > 3) {
		cout << "You must enter a number between 1-3!" << endl;
		cin >> num;
	}
	Dice Dice(num);
	Dice.rollDice(num);
	return 0;
}*/