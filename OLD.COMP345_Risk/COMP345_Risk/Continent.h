#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Country.h"

class Continent
{
public:
	Continent(std::string name);
	void setContainedCountries(Country* country);
	void setNeiboringContinents(Continent* continent);
	bool isContinentNotValid();
	std::string getContinentName();
private:
	std::string continent_name;
	std::vector<Country*> contained_countries;
	std::vector<Continent*> neighboring_continent;
protected:
};

