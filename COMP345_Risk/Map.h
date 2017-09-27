#pragma once

#include <string>
#include <vector>
#include <iostream>
class Continent;
class Country;

class Map
{
public:
	Map();

	void setContainedContinents(Continent* continent);
	void setContainedCountries(Country* country);
	Country* getCountryFromMapByName(std::string countryName);
	bool containsCountry(Country c);
	bool isMapNotValid();
	bool isCountryExist();
	bool isContinentExist();

private:
	std::vector <Continent*> contained_continent;
	std::vector <Country*> contained_country_map;
};

class Continent
{
public:
	Continent(std::string name);

	void setContainedCountries(Country *country);
	void setNeighboringContinents(Continent *continent);
	bool isContinentNotValid();
	std::string getContinentName();
private:
	std::string continent_name;
	std::vector<Country*> contained_country_cont;
	std::vector<Continent*> neighboring_continent;
};

class Country
{
public:
	Country();
	Country(std::string name);

	void setNeighboringCountries(Country* neighbor);
	void setCountryName(std::string name);
	void setTroopNumber(int numberOfTroops);
	void setOwner(std::string ownerOfCountry);
	void setContinent(std::string insideContinent);
	void setX(int xCoord);
	void setY(int yCoord);

	std::vector<Country*> getNeighboringCountries();
	std::string getCountryName();
	int getTroopNumber();
	std::string getOwner();
	std::string getContinent();
	int getX();
	int getY();
	bool isCountryNotValid();
private:
	int troopNumber;
	std::string owner;
	std::string continent;
	std::string country_name;
	std::vector<Country*> neighboring_countries;
	int x;
	int y;
};

