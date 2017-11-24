#include "Dice.h"
#include "Player.h"
#include "Time.h"
#include "main.h"
#include "Game.h"
#include "GameStatus.h"
#include "CCODecorator.h"
#include "PDODecorator.h"
#include "TurnNumber.h"

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
		// Menu for a2.
		cout << "\n\nAssignment 2 Debug Menu" << endl;
		cout << "1- Start Game" << endl;
		cout << "2- Exit" << endl;

		cin >> selection;
		switch (selection) {
		case 1://Starts game.
			startGame();
			break;
		case 2://Exit
			exit(0);
			break;
		default:
			break;
		}
	} while (selection != 6);
}

void startGame() {
	//start game here. (Game.cpp)
	Game *game = new Game();
	GameStatus *gameStatus = new GameStatus(game);
	gameStatus = new CCODecorator(gameStatus, game);
	gameStatus = new PDODecorator(gameStatus, game);
	TurnNumber *turnCounter = new TurnNumber(game);
	game->startGame();
}