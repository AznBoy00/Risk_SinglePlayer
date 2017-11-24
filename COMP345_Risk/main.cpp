#include "Dice.h"
#include "Player.h"
#include "Time.h"
#include "main.h"
#include "Game.h"
#include "GameStatus.h"
#include "CCODecorator.h"
#include "PDODecorator.h"
#include "PHODecorator.h"
#include "TurnNumber.h"
#include "UserStrategy.h"
#include "AggroStrategy.h"
#include "PassiveStrategy.h"
#include "CheaterStrategy.h"
#include "RandomStrategy.h"
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
		cout << "\n\nAssignment 4 Debug Menu" << endl;
		cout << "1- Start Game (Part 1)" << endl;
		cout << "2- Start Tournament Demo" << endl;
		cout << "3- Exit" << endl;

		cin >> selection;
		switch (selection) {
		case 1://Starts game.
			startGame();
  		break;
		case 2://Starts game.
			startTournament();
			break;
		case 2://Exit
			exit(0);
			break;
		default:
			break;
		}
	} while (selection != 6);
}

void chooseDecorators(GameStatus* gs, Game* game) {
	static bool isPDOD = false;
	static bool isPHOD = false;
	static bool isCCOD = false;

	string s1 = (!isPDOD) ? "1 - Add Player Domination Observer Decorator\n" : "1 - Remove Player Domination Observer Decorator\n";
	string s2 = (!isPHOD) ? "2 - Add Player Hands Observer Decorator\n" : "2 - Remove Player Hands Observer Decorator\n";
	string s3 = (!isCCOD) ? "3 - Add Continent Control Observer Decorator\n" : "2 - Remove Continent Control Observer Decorator\n";
	cout << "Choose which decorators you would like to use/remove: " << endl;
	cout << s1;
	cout << s2;
	cout << s3;
	int input;
	cin >> input;
	while (input < 1 || input > 3) {
		cout << "Invalid option: please enter a number between 1 and 3." << endl;
	}

	switch (input) {
	case 1: 
		if (isPDOD) {
			gs = new GameStatus(game);
			isPDOD = false;
		}
		else {
			gs = new PDODecorator(gs, game);
			isPDOD = true;
		}
		break;
	case 2:
		if (isPHOD) {
			gs = new GameStatus(game);
			isPHOD = false;
		}
		else {
			gs = new PHODecorator(gs, game);
			isPHOD = true;
		}
		break;
	case 3:
		if (isCCOD) {
			delete gs;
			gs = new GameStatus(game);
			isCCOD = false;
		}
		else {
			gs = new CCODecorator(gs, game);
			isCCOD = true;
		}
		break;
	}
}

void startGame() {
	//start game here. (Game.cpp)
	Game *game = new Game();
	GameStatus *gs = new GameStatus(game);
	TurnNumber* tsm = new TurnNumber(game);
	srand(time(0));
	game->setWinnerId(-1);

	game->selectMap();
	game->initializePlayers();
	game->assignTurns();
	game->assignCountries();
	game->assignArmies();

	// Create deck and cards
	game->playDeck = new Deck();

	// Run every steps of the game here.
	for (int i = 0; i < game->turnVector.size(); i++) {
		game->turnVector[i]->setStrategy(new RandomStrategy(game->turnVector[i]));
	}
	while (game->getWinnerId() == -1) {
		for (int i = 0; i < game->turnVector.size(); i++) {
			game->turnCounter++;
			chooseDecorators(gs, game);
			game->turnVector.at(i)->executeTurn(game->loadedMap->getMap(), game->playDeck, game->turnVector, game);
			if (game->turnVector[i]->getWinner() == true) {
				game->setWinnerId(game->turnVector[i]->getId());
				cout << "\nThe winner is Player " << game->getWinnerId() << ". Congratulations!" << endl;
				break;
			}
    }
	}
}
