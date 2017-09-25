#pragma once

#include <string>
#include <vector>
#include "Country.h"
#include "Continent.h";


class Map
{
public:
	Map();
	void setContainedContinents(Continent* continent);
	void setContainedCountries(Country* country);
	bool isMapNotValid();
private:
	std::vector <Continent*> contained_continent;
	std::vector <Country*> contained_country;
};

