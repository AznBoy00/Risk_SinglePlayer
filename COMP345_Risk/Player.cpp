#include "Player.h"
#include "Dice.h"

#include <iostream>
using namespace std;

Player::Player() {
	Dice dice = Dice();
}

Player::Player(int newId) {
	id = newId;
	cout << "Player id: " << id << " created." << endl;//debug
	dice = new Dice();
	cout << "Dice object for player id: " << id << " created." << endl;//debug
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
