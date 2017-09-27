#include "Player.h"
#include "Dice.h"

#include <iostream>
using namespace std;

Player::Player() {
	Dice dice = Dice();
}

Player::Player(int newId) {
	id = newId;
	cout << "Player id: " << id << " created." << endl;
	Dice dice = Dice();
	cout << "Dice object for player id: " << id << " created." << endl;
}

Player::~Player() {
}

Dice Player::getDice() {
	return dice;
}

int Player::getId() {
	return id;
}

void Player::setId(int newId) {
	id = newId;
}
