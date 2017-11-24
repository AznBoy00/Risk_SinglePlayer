#include "Tournament.h"

Tournament::Tournament() {
	start();
}

void Tournament::start() {
	int input, mapNumber, gameNumber, playerNumber, turnNumber;
	//Winner stuff
	int winner;
	vector<string> map1W;
	vector<string> map2W;
	vector<string> map3W;
	vector<string> map4W;
	vector<string> map5W;

	//Define game parameters.
	do {
		cout << "How many computer players will play the game? (2-4)" << endl;
		cin >> input;
	} while (input < PLAYER_MIN || input > PLAYER_MAX);

	playerNumber = input;

	initializePlayers(playerNumber);
	assignStrategies(playerNumber);

	do {
		cout << "How many games will the players play per map?" << endl;
		cin >> input;
	} while (input < GAME_MIN || input > GAME_MAX);

	gameNumber = input;

	do {
		cout << "How many turns will there be before reaching a draw game state?" << endl;
		cin >> input;
	} while (input < TURN_MIN || input > TURN_MAX);

	turnNumber = input;

	do {
		cout << "How many maps will the players play?" << endl;
		cin >> input;
	} while (input < MAP_MIN || input > MAP_MAX);

	mapNumber = input;

	//load game object instances
	for (int i = 0; i < mapNumber; i++) {
		cout << "\nMAP " << i + 1 << endl;
		input = selectMap();
		switch (i) {
		case 0:
			for (int j = 0; j < gameNumber; j++) {
				cout << "Game " << j + 1 << endl;
				Game* g = new Game(playerVector, playersStatus);
				map1Games.push_back(g);
				map1Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		case 1:
			for (int j = 0; j < gameNumber; j++) {
				cout << "Game " << j + 1 << endl;
				Game* g = new Game(playerVector, playersStatus);
				map2Games.push_back(g);
				map2Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		case 2:
			for (int j = 0; j < gameNumber; j++) {
				cout << "Game " << j + 1 << endl;
				Game* g = new Game(playerVector, playersStatus);
				map3Games.push_back(g);
				map3Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		case 3:
			for (int j = 0; j < gameNumber; j++) {
				cout << "Game " << j + 1 << endl;
				Game* g = new Game(playerVector, playersStatus);
				map4Games.push_back(g);
				map4Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		case 4:
			for (int j = 0; j < gameNumber; j++) {
				cout << "Game " << j + 1 << endl;
				Game* g = new Game(playerVector, playersStatus);
				map5Games.push_back(g);
				map5Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		default:
			cout << "An error has occured." << endl;
			break;
		}
	}

	winner = map1Games.at(0)->startGame(turnNumber);
	map1W.push_back(convertWinner(winner));
	winner = map1Games.at(1)->startGame(turnNumber);
	map1W.push_back(convertWinner(winner));

	/*for (int j = 0; j < gameNumber; j++) {
		winner = map1Games.at(j)->startGame(turnNumber);
		map1W.push_back(convertWinner(winner));
	}*/

	//Tournament game loops
	/*for (int i = 0; i < mapNumber; i++) {
		switch (i) {
		case 0:
			for (int j = 0; j < gameNumber; j++) {
				map1Games.at(j)->startGame(turnNumber);
			}
			break;
		case 1:
			for (int j = 0; j < gameNumber; j++) {
				map2Games.at(j)->startGame(turnNumber);
			}
			break;
		case 2:
			for (int j = 0; j < gameNumber; j++) {
				map3Games.at(j)->startGame(turnNumber);
			}
			break;
		case 3:
			for (int j = 0; j < gameNumber; j++) {
				map4Games.at(j)->startGame(turnNumber);
			}
			break;
		case 4:
			for (int j = 0; j < gameNumber; j++) {
				map5Games.at(j)->startGame(turnNumber);
			}
			break;
		default:
			cout << "An error has occured." << endl;
			break;
		}
	}*/

	//display stats
	cout << "\t\tM: ";
	for (int i = 0; i < mapNumber; i++) {
		if (i == 0) {
			cout << "Map 1";
		} else {
			cout << ", Map " << i + 1;
		}
	}
	cout << endl;

	cout << "\t\tP: ";
	for (int i = 0; i < playerNumber; i++) {
		if (i == 0) {
			cout << convertWinner(playerVector.at(i)->getStrategyId());
		} else {
			cout << ", " << convertWinner(playerVector.at(i)->getStrategyId());
		}
	}
	cout << endl;

	cout << "\t\tG: " << gameNumber << endl;
	cout << "\t\tD: " << turnNumber << endl;

	cout << "\t";
	for (int i = 0; i < gameNumber; i++) {
		cout << "\t|Game" << i + 1;
	}
	for (int i = 0; i < mapNumber; i++) {
		cout << "Map\t" << i;
		for (int j = 0; j < gameNumber; j++) {
			switch (j) {
				case 0:
					cout << "\t|" << map1W.at(j);
					break;
				case 1:
					cout << "\t|" << map2W.at(j);
					break;
				case 2:
					cout << "\t|" << map3W.at(j);
					break;
				case 3:
					cout << "\t|" << map4W.at(j);
					break;
				case 4:
					cout << "\t|" << map5W.at(j);
					break;
				default:
					break;
			}
		}
		cout << endl;
	}
}

int Tournament::selectMap() {
	// Initialize main data.
	struct dirent *directory;
	cout << "Select a map from the list: \n";
	DIR* mapDir = opendir("./Map Files/");
	int mapNumber = 0;
	vector<string> mapList;

	// Initialize maps
	if (mapDir) {
		while ((directory = readdir(mapDir)) != NULL) {
			mapList.push_back(directory->d_name);
			cout << mapNumber + 1 << " - " << directory->d_name << endl;
			mapNumber++;
		}
		int mapChoice;
		cin >> mapChoice;
		closedir(mapDir);
		return mapChoice;
	} else {
		cout << "Invalid input, try again." << endl;
		selectMap();
	}
}

//No input map selection
MapLoader* Tournament::selectMap(int input) {
	// Initialize main data.

	struct dirent *directory;
	//cout << "Select a map from the list: \n";
	DIR* mapDir = opendir("./Map Files/");
	int mapNumber = 0;
	vector<string> mapList;

	// Initialize maps
	if (mapDir) {
		while ((directory = readdir(mapDir)) != NULL) {
			mapList.push_back(directory->d_name);
			//cout << mapNumber + 1 << " - " << directory->d_name << endl;
			mapNumber++;
		}
		int mapChoice = input;
		MapLoader* loadedMap = new MapLoader(mapList.at(mapChoice - 1));
		closedir(mapDir);
		return loadedMap;
	}
	else {
		//cout << "Invalid input, try again." << endl;
		selectMap();
	}
}

//Call this only once
void Tournament::initializePlayers(int playerNumber) {
	for (int i = 0; i < playerNumber; i++) {
		Player* p = new Player(i + 1);
		playersStatus.push_back(new PlayerStatus(p));
		playerVector.push_back(p);
	}
}

void Tournament::assignStrategies(int playerNumber) {
	int input;
	cout << "1- Aggressive Computer" << endl;
	cout << "2- Benevolent Computer" << endl;
	cout << "3- Random Computer" << endl;
	cout << "4- Cheater Computer" << endl;
	for (int i = 0; i < playerNumber; i++) {
		do {
			cout << "What type of strategy will computer player " << i + 1 << " be? (1-4)" << endl;
			cin >> input;
		} while (input < 1 || input > 4);
		switch (input) {
		case 1:
			playerVector.at(i)->setStrategy(new AggroStrategy(playerVector.at(i)));
			break;
		case 2:
			playerVector.at(i)->setStrategy(new PassiveStrategy(playerVector.at(i)));
			break;
		case 3:
			playerVector.at(i)->setStrategy(new RandomStrategy(playerVector.at(i)));
			break;
		case 4:
			playerVector.at(i)->setStrategy(new CheaterStrategy(playerVector.at(i)));
			break;
		default:
			playerVector.at(i)->setStrategy(new UserStrategy(playerVector.at(i)));
			break;
		}
	}
}

string Tournament::convertWinner(int winner) {
	int winnerId = winner;
	if (winner != 0) {
		winnerId = playerVector.at(winnerId - 1)->getStrategyId();
	}
	switch (winnerId) {
	case 0:
		return "Draw";
		break;
	case 1:
		return "Aggressive";
		break;
	case 2:
		return "Benevolent";
		break;
	case 3:
		return "Random";
		break;
	case 4:
		return "Cheater";
		break;
	default:
		return "Error";
		break;
	}
}