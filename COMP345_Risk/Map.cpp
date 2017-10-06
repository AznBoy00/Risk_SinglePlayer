#include "Map.h"

//Map Initialization
Map::Map() {
}

void Map::setContainedContinentInMap(Continent* continent){
    containedContinentsInMap.push_back(continent);
}

void Map::setContainedCountryInMap(Country* country){
    containedCountriesInMap.push_back(country);
}
    
std::vector<Continent*> Map::getContainedContinentsInMap(){
    return containedContinentsInMap;
}

std::vector<Country*> Map::getContainedCountriesInMap(){
    return containedCountriesInMap;
}

Country* Map::getCountryByName(std::string nameOfCountry){
	for (unsigned int i = 0; i < containedCountriesInMap.size(); i++){
		if (containedCountriesInMap[i]->nameOfCountry == nameOfCountry){
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

bool Map::isMapContainsCountry(std::string nameOfCountry){
	for (unsigned int i = 0; i < containedCountriesInMap.size(); i++){
		if (containedCountriesInMap[i]->nameOfCountry == nameOfCountry){
			return true;
		}
	}
	return false;
}

bool Map::isMapContainsContinent(std::string nameOfContinent) {
	for (unsigned int i = 0; i < containedContinentsInMap.size(); i++) {
		if (containedContinentsInMap[i]->nameOfContinent == nameOfContinent) {
			return true;
		}
	}
	return false;
}

bool Map::isMapValid(){
	return (!isCountryInMultipleContinent() && isMapFullyConnected());
}

bool Map::isCountryInMultipleContinent(){
    for(unsigned int i = 0; i < containedContinentsInMap.size(); i++){
        for(unsigned int j = i+1; j < containedContinentsInMap.size(); j++){
            for(unsigned int k = 0; k < containedContinentsInMap[i]->containedCountriesInContinent.size(); k++){
                for(unsigned int l = 0; l < containedContinentsInMap[j]->containedCountriesInContinent.size(); l++){
                    if((containedContinentsInMap[i]->containedCountriesInContinent[k]->nameOfCountry) 
						== (containedContinentsInMap[j]->containedCountriesInContinent[l]->nameOfCountry)){
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

	for (unsigned int i = 0; i < country->neighboringCountries.size(); i++) {
		if (std::find(std::begin(visited), std::end(visited), country->neighboringCountries[i])
			== std::end(visited)) {
			depthFirstSearchForCountries(country->neighboringCountries[i], visited);
		}
		else{

		}
	}

}

void Map::depthFirstSearchForContinents(Continent* continent, std::vector<Continent*> &visited) {
	visited.push_back(continent);

	for (unsigned int i = 0; i < continent->neighboringContinents.size(); i++) {
		if (std::find(std::begin(visited), std::end(visited), continent->neighboringContinents[i])
			== std::end(visited)) {
			depthFirstSearchForContinents(continent->neighboringContinents[i], visited);
		}
	}
}

//Continent Initialization
Continent::Continent(){
}

void Continent::setNameOfContinent(std::string nameOfContinent){
    this->nameOfContinent = nameOfContinent;
}

void Continent::setNeighboringContinent(Continent* continent){
    neighboringContinents.push_back(continent);
}

void Continent::setContainedCountryInContinent(Country* country){
    containedCountriesInContinent.push_back(country);
}
    
std::string Continent::getNameOfContinent(){
    return nameOfContinent;
}
    
std::vector<Continent*> Continent::getNeighboringContinents(){
    return neighboringContinents;
}

std::vector<Country*> Continent::getContainedCountriesInContinent(){
    return containedCountriesInContinent;
}

//Country Initialization
Country::Country(){
}

Country::Country(std::string nameOfCountry){
	this->nameOfCountry = nameOfCountry;
}

void Country::setNumberOfTroops(int numberOfTroops){
    this->numberOfTroops = numberOfTroops;
}

void Country::setNameOfCountry(std::string nameOfCountry){
    this->nameOfCountry = nameOfCountry;
}

void Country::setNeighboringCountry(Country* country){
    neighboringCountries.push_back(country);
}

void Country::setOwner(std::string owner){
    this->owner = owner;
}

void Country::setCoordinateX(int coordinateX){
	this->coordinateX = coordinateX;
}

void Country::setCoordinateY(int coordinateY){
	this->coordinateY = coordinateY;
}

void Country::setContinent(std::string continent) {
	this->continentName = continent;
}

int Country::getNumberOfTroops(){
    return numberOfTroops;
}

std::string Country::getNameOfCountry(){
    return nameOfCountry;
}

std::vector<Country*> Country::getNeighboringCountries(){
    return neighboringCountries;
}

std::string Country::getOwner(){
    return owner;
}

int Country::getCoordinateX(){
	return coordinateX;
}

int Country::getCoordinateY(){
	return coordinateY;
}

std::string Country::getContinent() {
	return continentName;
}