#include "Map.h"

Map::Map()
{
}

void Map::setContainedContinents(Continent* continent) {
	Map::contained_continent.push_back(continent);
}

void Map::setContainedCountries(Country* country) {
	Map::contained_country.push_back(country);
}

bool Map::isMapNotValid() {
	return Continent::isContinentNotValid || Country::isCountryNotValid;
}