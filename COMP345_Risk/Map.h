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

	void setContainedContinentInMap(Continent* continent);
	void setContainedCountryInMap(Country* country);
	std::vector<Continent*> getContainedContinentsInMap();
	std::vector<Country*> getContainedCountriesInMap();
	Country* getCountryByName(std::string nameOfCountry);
	Continent* getContinentByName(std::string nameOfContinent);

	bool containsCountry(std::string nameOfCountry);
	bool isMapContainsContinent(std::string nameOfContinent);
	bool isMapValid();
	bool isMapFullyConnected();

private:
	std::vector<Continent*> containedContinentsInMap;
	std::vector<Country*> containedCountriesInMap;
	void depthFirstSearchForCountries(Country* country, std::vector<Country*> &visited);
	void depthFirstSearchForContinents(Continent* continent, std::vector<Continent*> &visited);
	bool isCountryInMultipleContinent();
};

class Continent
{
public:
	Continent();

	void setNameOfContinent(std::string nameOfContinent);
	void setNeighboringContinent(Continent* continent);
	void setContainedCountryInContinent(Country* country);
	void setContinentValue(int value);

	std::string getNameOfContinent();
	std::vector<Continent*> getNeighboringContinents();
	std::vector<Country*> getContainedCountriesInContinent();
	int getContinentValue();

	friend Map;

private:
	std::string nameOfContinent;
	std::vector<Continent*> neighboringContinents;
	std::vector<Country*> containedCountriesInContinent;
	int continentValue;
};

class Country
{
public:
	Country();
	Country(std::string name);

	void setNumberOfTroops(int numberOfTroops);
	void setNameOfCountry(std::string nameOfCountry);
	void setNeighboringCountry(Country* country);
	void setCoordinateX(int coordinateX);
	void setCoordinateY(int coordinateY);
	void setContinent(std::string continent);
	void setOwnerNumber(int ownerOfCountry);

	std::vector<Country*> getNeighboringCountries();
	std::string getNameOfCountry();
	int getNumberOfTroops();
	int getOwnerNumber();
	std::string getContinent();
	int getCoordinateX();
	int getCoordinateY();

	void setVisited(bool v);
	bool getVisited();
	void visitCountry(Map m);

private:
	int numberOfTroops;
	int ownerNumber = 0;
	std::string nameOfCountry;
	std::string continentName;
	std::vector<Country*> neighboringCountries;
	int coordinateX;
	int coordinateY;
	bool visited;
};