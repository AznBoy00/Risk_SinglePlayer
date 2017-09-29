#include "Map.h"
#include <algorithm>
/*Default constructor*/
Map::Map()
{
}
/*Setter for containing continent object*/
void Map::setContainedContinents(Continent* continent) {
	Map::contained_continent.push_back(continent);
}
/*Setter for containing country*/
void Map::setContainedCountries(Country* country) {
	Map::contained_country_map.push_back(country);
}
/*Getter for containing continent object*/
std::vector<Country*> Map::getContainedCountries() {
	return Map::contained_country_map;
}
/*Getter for country from map by name*/
Country* Map::getCountryFromMapByName(std::string countryName){
	int i = 0;
	while(i < contained_country_map.size()){
		if (contained_country_map[i]->getCountryName().compare(countryName) == 0){
			return contained_country_map[i];
		}
		i++;
	}
}
/*Returns Boolean for an invalid map*/
bool Map::isMapNotValid(){
	if (contained_continent.empty()){
		return true;
	}
	return false;
}
/*Returns boolean if a map contains s country*/
bool Map::containsCountry(std::string s){ //rewrite this function
	for (int i = 0; i < contained_country_map.size(); i++) {
		if (contained_country_map[i]->getCountryName().compare(s) == 0) {
			return true;
		}
	}
	return false;
}
/*Constructor Continent*/
Continent::Continent(std::string name)
{
	continent_name = name;
}
/*Setter for contained countries*/
void Continent::setContainedCountries(Country* country) {
	contained_country_cont.push_back(country);
}
/*Setter for neighboring continents*/
void Continent::setNeighboringContinents(Continent* continent) {
	neighboring_continent.push_back(continent);
}
/*Returns a boolean for an invalid continent*/
bool Continent::isContinentNotValid() {
	return contained_country_cont.empty() || neighboring_continent.empty();
}
/*Getter of continent name*/
std::string Continent::getContinentName() {
	return continent_name;
}

/*Default constructor for Country*/
Country::Country()
{
}
/*Constructor accepting string name*/
Country::Country(std::string name){
	country_name = name;
}
/*Setter for neighboring country*/
void Country::setNeighboringCountries(Country * neighbor)
{
	Country::neighboring_countries.push_back(neighbor);
}
/*Setter for country name*/
void Country::setCountryName(std::string name) {
	country_name = name;
}
/*Setter for troop number*/
void Country::setTroopNumber(int numberOfTroops) {
	troopNumber = numberOfTroops;
}
/*Setter for owner of country*/
void Country::setOwner(std::string ownerOfCountry) {
	owner = ownerOfCountry;
}
/*Setter for continent*/
void Country::setContinent(std::string insideContinent) {
	continent = insideContinent;
}
/*Setter for coordinate X*/
void Country::setX(int coordX) {
	x = coordX;
}
/*Setter for coordinate Y*/
void Country::setY(int coordY) {
	y = coordY;
}
/*Getter for a vector of neighboring country*/
std::vector<Country*> Country::getNeighboringCountries(){
	return neighboring_countries;
}
/*Getter for country name*/
std::string Country::getCountryName() {
	return country_name;
}
/*Getter for troop number*/
int Country::getTroopNumber() {
	return troopNumber;
}
/*Getter of owner*/
std::string Country::getOwner() {
	return owner;
}
/*Getter for continent*/
std::string Country::getContinent() {
	return continent;
}
/*Returns boolean for valid country*/
bool Country::isCountryNotValid() {
	return neighboring_countries.empty();
}
/*Getter for x coordinate for a country*/
int Country::getX() {
	return x;
}
/*Getter for y coordinate for a country*/
int Country::getY() {
	return y;
}