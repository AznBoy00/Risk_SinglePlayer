#include "Country.h"

Country::Country(std::string name){
	country_name = name;
}
void Country::setNeighboringCountries(Country * neighbor)
{
	Country::neighboring_countries.push_back(neighbor);
}

void Country::setTroopNumber(int numberOfTroops) {
	troopNumber = numberOfTroops;
}

void Country::setOwner(Player* ownerOfCountry) {
	owner = ownerOfCountry;
}

void Country::setContinent(Continent* insideContinent) {
	continent = insideContinent;
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

Player* Country::getOwner() {
	return owner;
}

Continent* Country::getContinent() {
	return continent;
}

bool Country::isCountryNotValid() {
	return neighboring_countries.empty();
}