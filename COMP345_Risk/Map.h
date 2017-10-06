#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

class Continent;
class Country;

class Map {
public:
    Map();
    
    void setContainedContinentInMap(Continent* continent);
    void setContainedCountryInMap(Country* country);
    
    std::vector<Continent*> getContainedContinentsInMap();
    std::vector<Country*> getContainedCountriesInMap();
	Country* getCountryByName(std::string nameOfCountry);
	Continent* getContinentByName(std::string nameOfContinent);
	
	bool isMapContainsCountry(std::string nameOfCountry);
	bool isMapContainsContinent(std::string nameOfContinent);
	bool isMapValid();

private:
    std::vector<Continent*> containedContinentsInMap;
    std::vector<Country*> containedCountriesInMap ;
	void depthFirstSearchForCountries(Country* country, std::vector<Country*> &visited);
	void depthFirstSearchForContinents(Continent* continent, std::vector<Continent*> &visited);
	bool isCountryInMultipleContinent();
	bool isMapFullyConnected();
};

class Continent{
public:
    Continent();
    
    void setNameOfContinent(std::string nameOfContinent);
    void setNeighboringContinent(Continent* continent);
    void setContainedCountryInContinent(Country* country);
    
    std::string getNameOfContinent();
    std::vector<Continent*> getNeighboringContinents();
    std::vector<Country*> getContainedCountriesInContinent();
    
	friend Map;

private:
    std::string nameOfContinent;
    std::vector<Continent*> neighboringContinents;
    std::vector<Country*> containedCountriesInContinent;
};

class Country{
public:
    Country();
	Country::Country(std::string nameOfCountry);
    
    void setNumberOfTroops(int numberOfTroops);
    void setNameOfCountry(std::string nameOfCountry);
    void setNeighboringCountry(Country* country);
    void setOwner(std::string owner);
	void setCoordinateX(int coordinateX);
	void setCoordinateY(int coordinateY);
	void setContinent(std::string continent);
    
    int getNumberOfTroops();
    std::string getNameOfCountry();
    std::vector<Country*> getNeighboringCountries();
    std::string getOwner();
	int getCoordinateX();
	int getCoordinateY();
	std::string getContinent();

	friend Map;
	friend Continent;

private:
    int numberOfTroops;
    std::string nameOfCountry;
	std::string continentName;
    std::vector<Country*> neighboringCountries;
    std::string owner;
	int coordinateX;
	int coordinateY;
};
#endif