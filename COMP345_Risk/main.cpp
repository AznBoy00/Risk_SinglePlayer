#include "Dice.h"
#include "Player.h"
#include "Time.h"
#include "main.h"

#include <iostream>
using namespace std;

int main() {
	loadMenu();
	return 0;
}

void loadMenu() {
	int selection;
	cout << "Welcome to Team18's COMP345 Risk Game!" << endl;
	
	do {
		cout << "\n\nAssignment 1 Debug Menu" << endl;
		cout << "1- Read Map" << endl;
		cout << "2- Load Map" << endl;
		cout << "3- Roll Dice" << endl;
		cout << "4- Show player object/Action options" << endl;
		cout << "5- Card/Deck methods" << endl;
		cout << "6- Exit" << endl;

		cin >> selection;
		switch (selection) {
		case 1://Read map
			readMaps();
			break;
		case 2://Load map
			loadMaps();
			break;
		case 3://Roll Dice + Create players
			loadDice();
			break;
		case 4://Show player actions
			playerActions();
			break;
		case 5://Card/Deck method showoffs
			cardDeckMethods();
			break;
		case 6://Exit
			exit(0);
			break;
		default:
			break;
		}
	} while (selection != 6);
}

void readMaps() {
}

void loadMaps() {
}

void loadDice() {
	srand(time(0));
	int num;

	Player *p1 = new Player(1);
	Player *p2 = new Player(2);

	cout << "\nHow many dice(s) does Player 1 want to roll? (1-3)" << endl;
	cin >> num;
	while (num < 1 || num > 3) {
		cout << "You must enter a number between 1-3!" << endl;
		cin >> num;
	}

	cout << "Player " << p1->getId() << "'s dice roll number is now " << p1->getDiceRolled() << endl;
	p1->roll(num);

	cout << "\nHow many dice(s) does Player 2 want to roll? (1-3)" << endl;
	cin >> num;
	while (num < 1 || num > 3) {
		cout << "You must enter a number between 1-3!" << endl;
		cin >> num;
	}

	cout << "Player " << p1->getId() << "'s dice roll number is now " << p1->getDiceRolled() << endl;
	p2->roll(num);

	p1->showStats();
	p2->showStats();
}

void playerActions() {
}

void cardDeckMethods() {
}