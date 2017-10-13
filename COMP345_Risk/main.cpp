#include "Dice.h"
#include "Player.h"
#include "Time.h"
#include "main.h"
#include "MapLoader.h"
#include "Cards.h"

#include <iostream>
using namespace std;

int main() {
	loadMenu();
	return 0;
}

void loadMenu() {
	int selection;
	cout << "Welcome to Team18's COMP345 Risk Game!" << endl;
	cout << "Brought to you by Brandon, Shawn, Matthew and Kevin!" << endl;

	do {
		cout << "\n\nAssignment 2 Debug Menu" << endl;
		cout << "1- OPTION 1" << endl;
		cout << "2- OPTION 2" << endl;
		cout << "3- OPTION 3" << endl;
		cout << "4- OPTION 4" << endl;
		cout << "5- Exit" << endl;

		cin >> selection;
		switch (selection) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5://Exit
			exit(0);
			break;
		default:
			break;
		}
	} while (selection != 5);
}
