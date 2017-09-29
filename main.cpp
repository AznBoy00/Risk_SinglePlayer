#include "Dice.h"
#include "Deck.h"
#include "Player.h"
#include "Time.h"
#include "main.h"
#include "MapLoader.h"

#include <iostream>
using namespace std;

/*
	Main driver method.
*/
int main() {
	loadMenu();
	return 0;
}
/*
	Test menu for assignment 1.
*/
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
/*
	Load maps from map.cpp
*/
void loadMaps() {
	cout << "\n(Part 1 & 2)Map demo:" << endl;
	MapLoader("World.map");
	//system("pause");
}
/*
	Demonstrates the dice engine of the game.
*/
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
/*
	Shows a sample of the turn player's menu.
*/
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
/*
	Create a deck object, then cards will be drawn and shown until the deck decks out.
*/
void cardDeckMethods() {
	Deck newDeck = Deck();
	cout << "Deck created." << endl;
	newDeck.shuffle();
	cout << "Deck shuffled." << endl;

	Deck infantryArray[14];
	Deck artilleryArray[14];
	Deck cavalryArray[14];
	int infantrycounter, artillerycounter, cavalrycounter;

	for (int i = 0; i < 42; i++) {// loop to identify each card type from the deck
								 // and place them in a array of that said type
		if (newDeck[i].getType().compare("Infantry") == 0) {
			infantrycounter = 0;
			infantryArray[infantrycounter] = newDeck[i];
			infantrycounter++;
		}

		if (newDeck[i].getType().compare("Artillery") == 0) {
			artillerycounter = 0;
			artilleryArray[artillerycounter] = newDeck[i];
			artillerycounter++;
		}

		if (newDeck[i].getType().compare("Cavalry") == 0) {
			cavalrycounter = 0;
			cavalryArray[cavalrycounter] = newDeck[i];
			cavalrycounter++;
		}

	}

	for (int i = 0; i < 14; i++)
		infantryArray[i].print();
	cout << infantrycounter + " infantry cards" << endl;

	for (int i = 0; i < 14; i++)
		artilleryArray[i].print();
	cout << artillerycounter + " artillery cards" << endl;

	for (int i = 0; i < 14; i++)
		cavalryArray[i].print();
	cout << infantrycounter + " cavalry cards" << endl;

	Hand newHand = Hand();// create hand. 
	int play;
	cout << "Show me your moves." << endl;
	cout << " Enter 1 to draw or 2 to exchange hand and 3 to quit." << endl;

	cin >> play;
	if (play == 1) {
	newHand.draw();
	play = 0;
}
if (play == 2) {
	newHand.exchange();
	play = 0;
}
else exit(0);


}