#include "Dice.h"
#include "Time.h"
#include <iostream>
using namespace std;

/*
	Dice constructor.
*/
Dice::Dice(int num) {
	diceRollNumber = num;
	diceValue = new int[num];
}

/*
	Dice destructor.
*/
Dice::~Dice() {
	diceRollNumber = 0;
	diceValue[0];
}

/*
	@param int num
	rollDice method that will roll a dice x number of times depending on int num input.
*/
void Dice::rollDice(int num) {
	// Weird way to make ran() as random as possible.
	int r = (int)((6 * rand() / (RAND_MAX + 1.0)) + 1);
	int rr;
	for (size_t i = 0; i < num; i++) {
		rr = r;
		r = (int)((6 * rand() / (RAND_MAX + 1.0)) + 1);
		diceValue[i] = r;
	}
	// For debugging purpose
	for (size_t i = 0; i < Dice::getDiceRollNumber(); i++) {
		cout << diceValue[i] << endl;
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
	num = diceRollNumber;
}

//Debugging driver
int main() {
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
}


