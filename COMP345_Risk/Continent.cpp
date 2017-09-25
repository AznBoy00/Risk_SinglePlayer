#include "Continent.h"

Continent::Continent(std::string name)
{
	continent_name = name;
}

void Continent::setContainedCountries(Country* country) {
	 contained_countries.push_back(country);
}

void Continent::setNeiboringContinents(Continent* continent) {
	 neighboring_continent.push_back(continent);
}

bool Continent::isContinentNotValid() {
	return contained_countries.empty() || neighboring_continent.empty();
}

std::string Continent::getContinentName() {
	return continent_name;
}