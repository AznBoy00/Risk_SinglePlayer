#include "Dice.h"
#include "Player.h"
#include "Time.h"
#include "main.h"
#include "MapLoader.h"

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
		cout << "1- Load Map" << endl;
		cout << "2- Roll Dice" << endl;
		cout << "3- Show player object/Action options" << endl;
		cout << "4- Card/Deck methods" << endl;
		cout << "5- Exit" << endl;

		cin >> selection;
		switch (selection) {
		case 1://Load map
			loadMaps();
			break;
		case 2://Roll Dice + Create players
			loadDice();
			break;
		case 3://Show player actions
			playerActions();
			break;
		case 4://Card/Deck method showoffs
			cardDeckMethods();
			break;
		case 5://Exit
			exit(0);
			break;
		default:
			break;
		}
	} while (selection != 5);
}

void loadMaps() {
	MapLoader("World.map");
	//system("pause");
}

void loadDice() {
	srand(time(0));
	int num;

	Player *p1 = new Player(1);
	Player *p2 = new Player(2);

	cout << "\n(Part 3)Dice methods demo:" << endl;

	cout << "\nHow many dice(s) does Player 1 want to roll? (1-3)" << endl;
	cin >> num;
	while (num < 1 || num > 3) {
		cout << "You must enter a number between 1-3!" << endl;
		cin >> num;
	}
	p1->roll(num);

	cout << "\nHow many dice(s) does Player 2 want to roll? (1-3)" << endl;
	cin >> num;
	while (num < 1 || num > 3) {
		cout << "You must enter a number between 1-3!" << endl;
		cin >> num;
	}
	p2->roll(num);

	cout << "P1 stats" << endl;
	//p1->showStats();
	p1->getDice().showStats();

	cout << "P2 stats" << endl;
	p2->getDice().showStats();
	//p2->showStats();
}

void playerActions() {
	int selection;
	Player *p1 = new Player(1);

	cout << "\n(Part 4)Player(1) action menu demo:" << endl;
	cout << "Turn player action:" << endl;
	cout << "1-Show player info" << endl;
	cout << "2-Reinforce" << endl;
	cout << "3-Attack" << endl;
	cout << "4-Fortify" << endl;
	cin >> selection;

	switch (selection) {
	case 1:
		p1->showStats();
		break;
	case 2:
		p1->reinforce();
		break;
	case 3:
		p1->attack();
		break;
	case 4:
		p1->fortify();
		break;
	default:
		break;
	}
}

void cardDeckMethods() {
}