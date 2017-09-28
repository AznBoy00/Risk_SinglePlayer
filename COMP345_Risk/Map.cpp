#include "Map.h"

Map::Map()
{
}

void Map::setContainedContinents(Continent* continent) {
	Map::contained_continent.push_back(continent);
}

void Map::setContainedCountries(Country* country) {
	Map::contained_country_map.push_back(country);
}

Country* Map::getCountryFromMapByName(std::string countryName){
	int i = 0;
	while(i < contained_country_map.size){
		if (contained_country_map[i]->getCountryName.compare(countryName) == 0){
			return contained_country_map[i];
		}
		i++;
	}
}

bool Map::isMapNotValid(){
	if (contained_continent.empty()){
		return true;
	}
}
bool Map::containsCountry(Country c){
	if (find(contained_country_map.begin(), contained_country_map.end(), c) != contained_country_map.end()){
		return true;
	}
	else return false;
}

//Nope

Continent::Continent(std::string name)
{
	continent_name = name;
}

void Continent::setContainedCountries(Country* country) {
	contained_country_cont.push_back(country);
}

void Continent::setNeighboringContinents(Continent* continent) {
	neighboring_continent.push_back(continent);
}

bool Continent::isContinentNotValid() {
	return contained_country_cont.empty() || neighboring_continent.empty();
}

std::string Continent::getContinentName() {
	return continent_name;
}

//Nope

Country::Country()
{
}

Country::Country(std::string name){
	country_name = name;
}
void Country::setNeighboringCountries(Country * neighbor)
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
	x = coordX;
}

void Country::setY(int coordY) {
	y = coordY;
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

int Country::getX() {
	return x;
}

int Country::getY() {
	return y;
}