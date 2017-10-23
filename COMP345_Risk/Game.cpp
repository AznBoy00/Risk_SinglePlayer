#include <iostream>
#include <vector>
#include "Game.h"
#include "Player.h"
#include <dirent.h>
#include "MapLoader.h"

Game::Game() {
	MapLoader* loadedMap = NULL;
	struct dirent *directory;
	cout << "Select a map from the list: ";
	DIR* mapDir = opendir("./Map Files/");
	int mapNumber = 0;
	vector<string> mapList;
	if (mapDir) {
		while ((directory = readdir(mapDir)) != NULL) {
			mapList.push_back(directory->d_name);
			cout << mapNumber + 1 << " - " << directory->d_name << endl;
			mapNumber++;
		}
		int mapChoice;
		cin >> mapChoice;
		loadedMap = new MapLoader(mapList.at(mapChoice-1));
		closedir(mapDir);
	}

	cout << "How many players are in the game? (2-6)";
	cin >> numOfPlayers;
	if (numOfPlayers < 2 || numOfPlayers > 6) {
		cout << "Entered number of players not within accept range." << endl;
	}
	for (int i = 0; i < numOfPlayers; i++) {
		playerVector.push_back(new Player(i + 1));
	}

	//turn assignment
	for(int i = 1; i <= numOfPlayers; i++) {
		int rando;
		rando = rand() % numOfPlayers;
		while (playerVector.at(rando)->getTurnNumber() != 0) {
			rando = rand() % numOfPlayers;
		}
		playerVector.at(rando)->setTurnNumber(i);
		cout << "Player " << rando + 1 << " with turn number " << i;
	}

	//country assignment
	int countryCount = 0;
	cout << "Number of countries is " << loadedMap->getMap()->getContainedCountriesInMap().size() << endl;
	while (countryCount < loadedMap->getMap()->getContainedCountriesInMap().size()) {
		for (int i = 0; i < numOfPlayers; i++) {
			int randomCountryNumber;
			randomCountryNumber = rand() % loadedMap->getMap()->getContainedCountriesInMap().size();
			Country* assignedCountry = loadedMap->getMap()->getContainedCountriesInMap().at(randomCountryNumber);
			while (assignedCountry->getOwnerNumber() != 0) {
				randomCountryNumber = rand() % loadedMap->getMap()->getContainedCountriesInMap().size();
				assignedCountry = loadedMap->getMap()->getContainedCountriesInMap().at(randomCountryNumber);
			}
			assignedCountry->setOwnerNumber(i + 1);
			playerVector.at(i)->setOwnedCountry(assignedCountry);
			countryCount++;
			cout << countryCount << " Country called " << assignedCountry->getNameOfCountry() << " is assigned to Player " << i + 1 << endl;
		}
	}

	//army assignment
	int numberOfArmies;
	numberOfArmies = 50 - numOfPlayers * 5;
	for (int i = 0; i < numOfPlayers; i++) {
		cout << "Player " << i << " :";
	}
	





	

}
