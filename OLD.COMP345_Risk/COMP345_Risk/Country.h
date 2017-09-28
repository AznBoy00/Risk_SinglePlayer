#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Continent.h"

class Country
{
public:
	Country(std::string name);

	void setNeighboringCountries(Country* neighbor);
	void setTroopNumber(int numberOfTroops);
	void setOwner(Player* ownerOfCountry);
	void setContinent(Continent* insideContinent);

	std::vector<Country*> getNeighboringCountries();
	std::string getCountryName();
	int getTroopNumber();
	Player* getOwner();
	Continent* getContinent();
	bool isCountryNotValid();
private:
	int troopNumber;
	Player* owner;
	Continent* continent;
	std::string country_name;
	std::vector<Country*> neighboring_countries;
};

