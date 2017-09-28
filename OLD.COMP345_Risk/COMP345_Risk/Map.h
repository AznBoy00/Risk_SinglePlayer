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
	bool isMapNotValid();

private:
	std::vector <Continent*> contained_continent;
	std::vector <Country*> contained_country_in_map;
	void DepthFirstSearch(Country* startingPoint, std::vector<Country*> listVisited);
};

class Continent{

private:
	std::string continent_name;
	std::vector<Country*> contained_country_in_continent;
	std::vector<Continent*> neighboring_continent;

public:
	Continent(std::string name);

	void setContainedCountry(Country *country);
	void setNeighboringContinent(Continent *continent);

	std::string getContinentName();
	std::vector<Country*> getContainedCountriesInContinent();
	std::vector<Continent*> getNeighboringContinents();
	bool isContinentNotValid();
};

class Country{

private:
	int troopNumber;
	std::string owner;
	std::string continent;
	std::string country_name;
	std::vector<Country*> neighboring_countries;
	int coordinate_X;
	int coordinate_Y;

public:
	Country(std::string name);

	void setNeighboringCountry(Country* neighbor);
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
	bool isCountryNotValid();
	int getCoordinateX();
	int getCoordinateY();
};

