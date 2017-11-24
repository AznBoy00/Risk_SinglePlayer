#include "Map.h"
#include <algorithm>

//Map Initialization
Map::Map() {
}

void Map::setContainedContinentInMap(Continent* continent) {
	containedContinentsInMap.push_back(continent);
}

void Map::setContainedCountryInMap(Country* country) {
	containedCountriesInMap.push_back(country);
}

std::vector<Continent*> Map::getContainedContinentsInMap() {
	return containedContinentsInMap;
}

std::vector<Country*> Map::getContainedCountriesInMap() {
	return containedCountriesInMap;
}

Country* Map::getCountryByName(std::string nameOfCountry) {
	for (unsigned int i = 0; i < containedCountriesInMap.size(); i++) {
		if (containedCountriesInMap[i]->getNameOfCountry() == nameOfCountry) {
			return containedCountriesInMap[i];
		}
	}
	return NULL;
}

Continent* Map::getContinentByName(std::string nameOfContinent) {
	for (unsigned int i = 0; i < containedContinentsInMap.size(); i++) {
		if (containedContinentsInMap[i]->nameOfContinent == nameOfContinent) {
			return containedContinentsInMap[i];
		}
	}
	return NULL;
}


bool Map::isMapValid() {
	return (!isCountryInMultipleContinent() && isMapFullyConnected());
}
bool Map::isCountryInMultipleContinent() {
	for (unsigned int i = 0; i < containedContinentsInMap.size(); i++) {
		for (unsigned int j = i + 1; j < containedContinentsInMap.size(); j++) {
			for (unsigned int k = 0; k < containedContinentsInMap[i]->containedCountriesInContinent.size(); k++) {
				for (unsigned int l = 0; l < containedContinentsInMap[j]->containedCountriesInContinent.size(); l++) {
					if ((containedContinentsInMap[i]->containedCountriesInContinent[k]->getNameOfCountry())
						== (containedContinentsInMap[j]->containedCountriesInContinent[l]->getNameOfCountry())) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Map::isMapFullyConnected() {

	if (containedContinentsInMap.size() == 0 || containedCountriesInMap.size() == 0) {
		return false;
	}

	std::vector<Country*> visitedCountries;
	depthFirstSearchForCountries(containedCountriesInMap[0], visitedCountries);

	std::vector<Continent*> visitedContinents;
	depthFirstSearchForContinents(containedContinentsInMap[0], visitedContinents);

	if (visitedContinents.size() == containedContinentsInMap.size() && visitedCountries.size() == containedCountriesInMap.size()) {
		return true;
	}
	else {
		return false;
	}
}

void Map::depthFirstSearchForCountries(Country* country, std::vector<Country*> &visited) {
	visited.push_back(country);

	for (unsigned int i = 0; i < country->getNeighboringCountries().size(); i++) {
		if (std::find(std::begin(visited), std::end(visited), country->getNeighboringCountries()[i])
			== std::end(visited)) {
			depthFirstSearchForCountries(country->getNeighboringCountries()[i], visited);
		}
		else {

		}
	}

}

void Map::depthFirstSearchForContinents(Continent* continent, std::vector<Continent*> &visited) {
	visited.push_back(continent);

	for (unsigned int i = 0; i < continent->getNeighboringContinents().size(); i++) {
		if (std::find(std::begin(visited), std::end(visited), continent->getNeighboringContinents()[i])
			== std::end(visited)) {
			depthFirstSearchForContinents(continent->getNeighboringContinents()[i], visited);
		}
	}
}

bool Map::containsCountry(std::string s) { //rewrite this function
	for (int i = 0; i < containedCountriesInMap.size(); i++) {
		if (containedCountriesInMap[i]->getNameOfCountry().compare(s) == 0) {
			return true;
		}
	}
	return false;
}

//Nope

//Continent Initialization
Continent::Continent() {
}

void Continent::setNameOfContinent(std::string nameOfContinent) {
	this->nameOfContinent = nameOfContinent;
}

void Continent::setNeighboringContinent(Continent* continent) {
	neighboringContinents.push_back(continent);
}

void Continent::setContainedCountryInContinent(Country* country) {
	containedCountriesInContinent.push_back(country);
}

void Continent::setContinentValue(int value) {
	continentValue = value;
}

std::string Continent::getNameOfContinent() {
	return nameOfContinent;
}

std::vector<Continent*> Continent::getNeighboringContinents() {
	return neighboringContinents;
}

std::vector<Country*> Continent::getContainedCountriesInContinent() {
	return containedCountriesInContinent;
}

int Continent::getContinentValue() {
	return continentValue;
}

//Nope

Country::Country()
{
}

Country::Country(std::string nameOfCountry) {
	this->nameOfCountry = nameOfCountry;
}

void Country::setNumberOfTroops(int numberOfTroops) {
	this->numberOfTroops = numberOfTroops;
}

void Country::setNameOfCountry(std::string nameOfCountry) {
	this->nameOfCountry = nameOfCountry;
}

void Country::setNeighboringCountry(Country* country) {
	neighboringCountries.push_back(country);
}


void Country::setOwnerNumber(int ownerOfCountry) {
	ownerNumber = ownerOfCountry;
}

void Country::setCoordinateX(int coordinateX) {
	this->coordinateX = coordinateX;
}

void Country::setCoordinateY(int coordinateY) {
	this->coordinateY = coordinateY;
}

void Country::setContinent(std::string continent) {
	this->continentName = continent;
}


std::vector<Country*> Country::getNeighboringCountries() {
	return neighboringCountries;
}

std::string Country::getNameOfCountry() {
	return nameOfCountry;
}

int Country::getNumberOfTroops() {
	return numberOfTroops;
}

int Country::getOwnerNumber() {
	return ownerNumber;
}

std::string Country::getContinent() {
	return continentName;
}

int Country::getCoordinateX() {
	return coordinateX;
}

int Country::getCoordinateY() {
	return coordinateY;
}

void Country::setVisited(bool v) {
	visited = v;
}

bool Country::getVisited() {
	return visited;
}

void Country::visitCountry(Map m) {
	static int visits = 0;
	for (int i = 0; i < this->getNeighboringCountries().size(); i++) {
		if (this->getNeighboringCountries().at(i)->getVisited() == false) {
			this->getNeighboringCountries().at(i)->setVisited(true);
			this->getNeighboringCountries().at(i)->visitCountry(m);
			visits++;
		}
	}
	if (visits == m.getContainedCountriesInMap().size()) {
		//std::cout << "Map connectivity validated." << std::endl;
	}

}

std::vector<Country*> Country::getEnemies() {
	std::vector<Country*> enemies;
	for (int i = 0; i < this->getNeighboringCountries().size(); i++) {
		Country* neighbor = this->getNeighboringCountries().at(i);
		if (neighbor->getOwnerNumber() != this->getOwnerNumber()) {
			enemies.push_back(neighbor);
		}
	}
	return enemies;
}

std::vector<Country*> Country::getAllies() {
	std::vector<Country*> allies;
	for (int i = 0; i < this->getNeighboringCountries().size(); i++) {
		Country* neighbor = this->getNeighboringCountries().at(i);
		if (neighbor->getOwnerNumber() == this->getOwnerNumber()) {
			allies.push_back(neighbor);
		}
	}
	return allies;
}
