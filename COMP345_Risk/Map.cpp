#include "Map.h"

//Map Class Initialization
Map::Map()
{
	std::cout << "Map has been created." << std::endl;
}

void Map::setContainedContinents(Continent* continent) {
	Map::contained_continent.push_back(continent);
}

void Map::setContainedCountries(Country* country) {
	contained_country_in_map.push_back(country);
}

Country* Map::getCountryFromMapByName(std::string countryName){
	int i = 0;
	while(i < contained_country_in_map.size){
		if (contained_country_in_map[i]->getCountryName.compare(countryName) == 0){
			return contained_country_in_map[i];
		}
		i++;
	}
}

bool Map::isMapNotValid(){

	for (int i = 0; i < contained_continent.size; i++) {
		if (contained_continent[i]->isContinentNotValid()) {
			return true;
		}
	}


	for (int i = 0; i < contained_continent.size; i++) {
		if (contained_country_in_map[i]->isCountryNotValid()) {
			return true;
		}
	}

	int numberOfCountriesCounted = 0;
	for (int i = 0; i < contained_continent.size; i++) {
		for (int j = 0; j < contained_continent[i]->getContainedCountriesInContinent.size; j++) {
			numberOfCountriesCounted++;
		}
	}
	if (numberOfCountriesCounted != contained_country_in_map.size) {
		return true;
	}

	std::vector<Country*> listOfCountriesVisited;
	DepthFirstSearch(contained_country_in_map[0], listOfCountriesVisited);
	
	if (listOfCountriesVisited.size != contained_country_in_map) {
		return true;
	}

}
/*bool Map::containsCountry(Country c){
	if (find(contained_country_map.begin(), contained_country_map.end(), c) != contained_country_map.end()){
		return true;
	}
	else return false;
}*/

void DepthFirstSearch(Country* currentPoint, std::vector<Country*> listVisited) {
	if (std::find(listVisited.begin(), listVisited.end(), currentPoint) != listVisited.end()) {
		return;
	}

	listVisited.push_back(currentPoint);
	for (int i = 0; i < currentPoint->getNeighboringCountries.size; i++) {
		if (std::find(listVisited.begin(), listVisited.end(), currentPoint->getNeighboringCountries[i]) != listVisited.end()) {
			DepthFirstSearch(currentPoint->getNeighboringCountries[i], listVisited);
		}
	}
}

//Continent Class Initialization

Continent::Continent(std::string name)
{
	continent_name = name;
}

void Continent::setContainedCountry(Country* country) {
	contained_country_in_continent.push_back(country);
}

void Continent::setNeighboringContinent(Continent* continent) {
	neighboring_continent.push_back(continent);
}

std::string Continent::getContinentName() {
	return continent_name;
}

std::vector<Country*> Continent::getContainedCountriesInContinent()
{
	return contained_country_in_continent;
}

std::vector<Continent*> Continent::getNeighboringContinents()
{
	return neighboring_continent;
}

bool Continent::isContinentNotValid() {
	return contained_country_in_continent.empty() || neighboring_continent.empty();
}

//Country Class Initialization

Country::Country(std::string name){
	country_name = name;
}
void Country::setNeighboringCountry(Country* neighbor)
{
	Country::neighboring_countries.push_back(neighbor);
}

void Country::setCountryName(std::string name) {
	country_name = name;
}

void Country::setTroopNumber(int numberOfTroops) {
	troopNumber = numberOfTroops;
}

void Country::setOwner(std::string ownerOfCountry) {
	owner = ownerOfCountry;
}

void Country::setContinent(std::string insideContinent) {
	continent = insideContinent;
}

void Country::setX(int coordX) {
	coordinate_X = coordX;
}

void Country::setY(int coordY) {
	coordinate_Y = coordY;
}

std::vector<Country*> Country::getNeighboringCountries(){
	return neighboring_countries;
}

std::string Country::getCountryName() {
	return country_name;
}

int Country::getTroopNumber() {
	return troopNumber;
}

std::string Country::getOwner() {
	return owner;
}

std::string Country::getContinent() {
	return continent;
}

bool Country::isCountryNotValid() {
	return neighboring_countries.empty();
}

int Country::getCoordinateX() {
	return coordinate_X;
}

int Country::getCoordinateY() {
	return coordinate_Y;
}