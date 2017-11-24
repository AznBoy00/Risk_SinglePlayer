#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "MapLoader.h"
#include <algorithm>
using namespace std;

MapLoader::MapLoader(std::string fileDirectory) {
	ifstream inputfilestream;
	inputfilestream.open(fileDirectory);

	string line;
	bool hasTerritories = false;
	bool hasMap = false;
	bool hasContinents = false;

	map = new Map();
	while (getline(inputfilestream, line)) {

		if (hasContinents && !line.empty() && !hasTerritories) {
			if (line.find("[Territories]") != string::npos) {
				hasTerritories = true;
				continue;
			}
			Continent* continent = new Continent();
			stringstream ss(line);
			string word;
			vector<string> lineVector;

			while (getline(ss, word, '=')) {
				lineVector.push_back(word);
			}

			continent->setNameOfContinent(lineVector.at(0));
			continent->setContinentValue(stoi(lineVector.at(1)));
			map->setContainedContinentInMap(continent);

		}

		//if the [Territory] header is found and line is not empty, start reading
		if (hasTerritories && !line.empty()) {
			//create a country based on the info read on that line
			Country* territory = new Country();
			stringstream ss(line);
			string word;
			vector<string> lineVector;
			//store each read word in the line into a vector
			while (getline(ss, word, ',')) {
				lineVector.push_back(word);
			}
			//set Country's member values based on the words that are read
			if (!map->containsCountry(lineVector.at(0))) {

				territory->setNameOfCountry(lineVector.at(0));
				territory->setCoordinateX(stoi(lineVector.at(1))); //converting X to int
				territory->setCoordinateY(stoi(lineVector.at(2))); //converting Y to int
				territory->setContinent(lineVector.at(3));
				map->getContinentByName(lineVector.at(3))->setContainedCountryInContinent(territory);
				map->setContainedCountryInMap(territory); //add that country to the list of countries in the map
			}
			else {
				std::cout << "Error: Duplicate country.";
				exit(0);
			}
		}


		//Checks for Map, Continent and Territories headers to validate map
		if (line.find("[Map]") != string::npos) {
			hasMap = true;
		}
		if (line.find("[Continents]") != string::npos) {
			hasContinents = true;

		}
		if (line.find("[Territories]") != string::npos && hasMap && hasContinents) {
			hasTerritories = true;
		}
	}
	hasTerritories = false;
	inputfilestream.clear();
	inputfilestream.seekg(0, std::ios::beg);
	while (getline(inputfilestream, line)) {
		//if the [Territory] header is found, start reading
		if (hasTerritories && !line.empty()) {
			stringstream ss(line);
			string word;
			vector<string> lineVector;
			//store each read word in the line into a vector
			while (getline(ss, word, ',')) {
				lineVector.push_back(word);
			}
			Country* territory = map->getCountryByName(lineVector.at(0));
			for (int i = 4; i < lineVector.size(); i++) {
				territory->setNeighboringCountry(map->getCountryByName(lineVector.at(i)));
			}
			for (int i = 0; i < map->getContainedCountriesInMap().size(); i++) {
				for (int j = 0; j < territory->getNeighboringCountries().size(); j++) {
					Continent* currentCont = map->getContinentByName(territory->getContinent());
					Continent* neighborCont = map->getContinentByName(territory->getNeighboringCountries().at(j)->getContinent());
					if (territory->getContinent().compare(territory->getNeighboringCountries().at(j)->getContinent()) != 0) {
						currentCont->setNeighboringContinent(neighborCont);
						//cout << currentCont->getNameOfContinent() << " is neighbors with " << neighborCont->getNameOfContinent() << endl;
					}
				}
			}

			std::cout << "Country name is: " << territory->getNameOfCountry() << endl;
			std::cout << "X: " << territory->getCoordinateX() << " Y: " << territory->getCoordinateY() << endl;
			std::cout << "Continent: " << territory->getContinent() << endl;
			std::cout << "Neighbors: ";
			for (int i = 0; i<territory->getNeighboringCountries().size(); i++) {
				std::cout << territory->getNeighboringCountries().at(i)->getNameOfCountry() << " ";
			}
			std::cout << endl;
		}

		if (line.find("[Territories]") != string::npos && hasMap && hasContinents) {
			hasTerritories = true;

		}
	}

	//If no checks are passed, map is invalid.
	if (!hasMap || !hasContinents || !hasTerritories) {
		std::cout << "Invalid map.";
		exit(0);
	}

	//Check for number of countries
	std::cout << "Number of countries: " << map->getContainedCountriesInMap().size() << endl;
	//Check neighbors to check graph connectivity
	map->getContainedCountriesInMap().at(0)->visitCountry(*map);
	//map->depthFirstSearchForCountries(map->getContainedCountriesInMap().at(0), map->getContainedCountriesInMap());
	cout << map->isMapFullyConnected();
	//delete m;

}

Map* MapLoader::getMap() {
	return map;
}

