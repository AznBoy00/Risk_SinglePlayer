#include <iostream>
#include <vector>
#include "Game.h"
#include "Player.h"
#include <dirent.h>
#include "MapLoader.h"
#include "Cards.h"

Game::Game() {
	MapLoader* loadedMap = NULL;
	struct dirent *directory;
	cout << "Select a map from the list: ";
	DIR* mapDir = opendir("./Map Files/");
	int mapNumber = 0;
	vector<string> mapList;
	winnerId = -1;

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
	do {
		cout << "How many players are in the game? (2-6)";
		cin >> numOfPlayers;
		if (numOfPlayers < 2 || numOfPlayers > 6) {
			cout << "Entered number of players not within accepted range." << endl;
		}
	} while (numOfPlayers < 2 || numOfPlayers > 6);

	for (int i = 0; i < numOfPlayers; i++) {
		playerVector.push_back(new Player(i + 1));
	}

	//turn assignment
	for(int i = 1; i <= numOfPlayers; i++) {
		int rando;
		rando = rand() % numOfPlayers; //generate random number
		while (playerVector.at(rando)->getTurnNumber() != 0) { //if that player has already been assigned a number, regenerate
			rando = rand() % numOfPlayers;
		}
		playerVector.at(rando)->setTurnNumber(i); //assign that turn number to the player
		cout << "\nPlayer " << rando + 1 << " with turn number " << i;
	}

	//country assignment
	int countryCount = 0;
	cout << "Number of countries is " << loadedMap->getMap()->getContainedCountriesInMap().size() << endl;
	//while all countries have not been allocated
	while (countryCount < loadedMap->getMap()->getContainedCountriesInMap().size()) {
		//allocating one country per player at a time (round-robin)
		for (int i = 0; i < numOfPlayers; i++) {
			int randomCountryNumber;
			randomCountryNumber = rand() % loadedMap->getMap()->getContainedCountriesInMap().size(); //generate random country number
			Country* assignedCountry = loadedMap->getMap()->getContainedCountriesInMap().at(randomCountryNumber);
			//if the country has already been allocated to someone, regenerate the number
			while (assignedCountry->getOwnerNumber() != 0) {
				randomCountryNumber = rand() % loadedMap->getMap()->getContainedCountriesInMap().size();
				assignedCountry = loadedMap->getMap()->getContainedCountriesInMap().at(randomCountryNumber);
			}
			assignedCountry->setOwnerNumber(i + 1); //set that country as owned by player i
			playerVector.at(i)->setOwnedCountry(assignedCountry); //add that country to list of owned countries
			countryCount++;
			cout << countryCount << " Country called " << assignedCountry->getNameOfCountry() << " is assigned to Player " << i + 1 << endl;
			if (countryCount == loadedMap->getMap()->getContainedCountriesInMap().size()) { //break out of loop when all countries have been allocated
				break;
			}
		}
	}

	//army assignment
	int numberOfArmies;
	numberOfArmies = 50 - (numOfPlayers * 5); //calculates number of armies per player
	//for each player, add one army to each of their owned countries and all the remaining ones go to the last country
	for (int i = 0; i < numOfPlayers; i++) {
		int troopsPerPlayer = 0; //int to count how many armies each player has placed
		for (int j = 0; j < playerVector.at(i)->getOwnedCountries().size(); j++) {
			if (j == playerVector.at(i)->getOwnedCountries().size() - 1) {
				playerVector.at(i)->getOwnedCountries().at(j)->setNumberOfTroops(numberOfArmies - j);
				troopsPerPlayer += numberOfArmies - j;
			} else {
				playerVector.at(i)->getOwnedCountries().at(j)->setNumberOfTroops(1);
				troopsPerPlayer += 1;
			}
		}
		cout << "Player " << i+1 << " has placed " << troopsPerPlayer << " troops." << endl;
	}

	// Create deck and cards
	Deck* playDeck = new Deck();
  
	// Run every steps of the game here.
	while (winnerId == -1) {
		int randomCountry;
		for (int i = 1; i <= playerVector.size(); i++) {
			for (int j = 0; j < playerVector.size(); j++) {
				if (playerVector.at(j)->getTurnNumber() == i) {
					cout << "Reinforment phase for player " << i + 1 << endl;
					playerVector.at(i)->reinforce(loadedMap->getMap(), playDeck);
					cout << "Attack phase for player " << i + 1 << endl;
					playerVector.at(i)->attack(loadedMap->getMap());
					cout << "Fortification phase for player " << i + 1 << endl;
					playerVector.at(i)->fortify();
				}
			}
		}
		winnerId = 1;
	}

	cout << "The winner is Player " << winnerId << ". Congratulations!" << endl;
}
