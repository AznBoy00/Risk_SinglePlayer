#include "Tournament.h"


Tournament::Tournament() {
	startGame();
}

void Tournament::startGame() {
	int input, mapNumber, gameNumber, playerNumber, turnNumber;

	do {
		cout << "How many computer players will play the game?" << endl;
		cin >> input;
	} while (input < PLAYER_MIN || input > PLAYER_MAX);

	playerNumber = input;

	do {
		cout << "How many games will the players play per map?" << endl;
		cin >> input;
	} while (input < GAME_MIN || input > GAME_MAX);

	gameNumber = input;

	do {
		cout << "How many maps will the players play?" << endl;
		cin >> input;
	} while (input < MAP_MIN || input > MAP_MAX);

	mapNumber = input;

	initializePlayers(playerNumber);

	for (size_t i = 0; i < mapNumber; i++) {
		cout << "MAP " << i + 1 << endl;
		input = selectMap();
		switch (i) {
		case 0:
			cout << "Game 1" << endl;
			for (size_t j = 0; j < gameNumber; j++) {
				Game* g = new Game(playerVector, playersStatus);
				map1Games.push_back(g);
				map1Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		case 1:
			cout << "Game 2" << endl;
			for (size_t j = 0; j < gameNumber; j++) {
				Game* g = new Game(playerVector, playersStatus);
				map2Games.push_back(g);
				map2Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		case 2:
			cout << "Game 3" << endl;
			for (size_t j = 0; j < gameNumber; j++) {
				Game* g = new Game(playerVector, playersStatus);
				map3Games.push_back(g);
				map3Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		case 3:
			cout << "Game 4" << endl;
			for (size_t j = 0; j < gameNumber; j++) {
				Game* g = new Game(playerVector, playersStatus);
				map4Games.push_back(g);
				map4Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		case 4:
			cout << "Game 5" << endl;
			for (size_t j = 0; j < gameNumber; j++) {
				Game* g = new Game(playerVector, playersStatus);
				map5Games.push_back(g);
				map5Games.at(j)->loadedMap = selectMap(input);
			}
			break;
		default:
			break;
		}
	}
}

int Tournament::selectMap() {
	// Initialize main data.
	struct dirent *directory;
	cout << "Select a map from the list: ";
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
	cout << "Select a map from the list: ";
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
		int mapChoice = input;
		MapLoader* loadedMap = new MapLoader(mapList.at(mapChoice - 1));
		closedir(mapDir);
		return loadedMap;
	}
	else {
		cout << "Invalid input, try again." << endl;
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