#include <iostream>
#include <vector>
#include "Game.h"
#include "Player.h"
#include <dirent.h>
#include "MapLoader.h"
#include "Dice.h"

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
	
	//attack phase starts here
		cout << "will you attack? Enter Yes or No." << endl; //decide attack or not to attack
		string attack;
		cin >> attack;

		if (attack == "no")
			cout << "End of attack phase" << endl;//if player doesnt want to attack then the phase ends and nothing happens.
		do {
			string attackingCountry;
			string attackTarget;

			cout << "Select which country is attacking." << endl; //player chooses which country is attacking.  
			cin >> attackingCountry;
			while(attackingCountry.getNumberOfTroops()< 2)
 {
				cout << "This country does not have enough armies to declare an attack. Choose another Country." << endl; // in case the player enters a country that does not have 2 armies
				cin >> attackingCountry;

			}if (attackingCountry.getNumberOfTroops() > 2) { // player selects which neighboring country he is attacking.
				cout << "Select which country " + attackingCountry + " is attacking." << endl;
				cin >> attackTarget;

				while (attackTargetisnotvalid)// checks if that country is a neighboring country. 
					cout << "You must choose a neighboring country" << endl;
				cin >> attackTarget;
			} if (attackTargetisvalid){ 
				
				// this is where the dice function starts. 
				
					int dice1;
					int dice2;
					int maxDice1;
					int maxDice2;
					string siege;
					// calculate how many dice the attacking player is allowed to roll. 

					if (attackingCountry.getNumberOfTroops() > 3)
						maxDice1 = 3;
					else maxDice1 = attackingCountry.getNumberOfTroops() - 1;

					// calculate how many dice the defending player is allowed to roll. 

					if (attackedCountry.getNumberOfTroops < 2)
						maxDice2 = 1;
					else maxDice2 = 2;

					cout << "Choose the number of dice for the attacking country. 1 to " + maxDice1 << endl;

					cin >> dice1;
					while (dice1 <1 || dice1 >maxDice1) { // check if number of dice chosen is a valid number within the max number of dices allowed. 
						cout << "This is not a valid number of dice. Enter the number of dice for the attacking country." << endl;
						cin >> dice1;
					}

					cout << "choose the number of dice for the defending country. " << endl;
					cin >> dice2;
					while (dice2 <1 || dice2>maxDice2) {
						cout << "This is not a valid number of dice. Enter the number of dice for the defending country." << endl;
					}

					//rolling the dice 
					int dice1Results[3];
					int dice2Results[2];

					for (int i = 0; i < maxDice1; i++) {// attacker rolls the dice and puts results in the array, which then will be sorted from highest to lowest.
						dice1Results[i] = rollDiceOnce(); //randomly generate a number from 1 to 6 and store in the array. 
					}
					// sorting the results from the attack dice roll. 
					for (int i = 0; i < maxDice1 - 1; i++) {
						if (dice1Results[i] < dice1Results[i + 1]) {
							int temp;
							temp = dice1Results[i];
							dice1Results[i] = dice1Results[i + 1];
							dice1Results[i + 1] = temp;
						}
					}if (dice1Results[0] < dice1Results[1]) {
						int temp;
						temp = dice1Results[0];
						dice1Results[0] = dice1Results[1];
						dice1Results[1] = temp;
					}
					// sorting the results from the defence dice roll.
					if (dice2Results[0] < dice2Results[1]) {
						int temp;
						temp = dice2Results[0];
						dice2Results[0] = dice2Results[1];
						dice2Results[1] = temp;
					}
					//comparing the winner
					for (int i = 0; i < maxDice2; i++) {


					}
				
			}

		} while (attack == "yes");



}
