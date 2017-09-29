#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "MapLoader.h"
#include <algorithm>/
using namespace std;

MapLoader::MapLoader(std::string fileDirectory) {
	ifstream inputfilestream;
	inputfilestream.open(fileDirectory);

	string line;
	bool hasTerritories = false;
	bool hasMap = false;
	bool hasContinents = false;

	Map* m = new Map();
	while (getline(inputfilestream, line)) {
		//if the [Territory] header is found, start reading
		if (hasTerritories) {
			//if line is not empty
			if (!line.empty()) {
				//create a country based on the info read on that line
				Country* territory = new Country();
				stringstream ss(line);
				string word;
				vector<string> lineVector;
				//store each read word in the line into a vector
				while (getline(ss, word, ',')) {
					lineVector.push_back(word);
				}
				//set Country's member values based on the words that are read
				territory->setCountryName(lineVector.at(0));
				territory->setX(stoi(lineVector.at(1))); //converting X to int
				territory->setY(stoi(lineVector.at(2))); //converting Y to int
				territory->setContinent(lineVector.at(3));
				m->setContainedCountries(territory); //add that country to the list of countries in the map

				for (int i = 4; i < lineVector.size(); i++) {
					//checks if map contains a certain country
					if (m->containsCountry(lineVector[i]) == false) {
						//if country is new, make a new country and add it to that country's list of neighbors
						Country* neighboringCountry = new Country(lineVector.at(i));
						territory->setNeighboringCountries(neighboringCountry);
					}
					else{
						//if country is already included in the map
						territory->setNeighboringCountries(m->getCountryFromMapByName(lineVector[i]));
					}
				}
				
				cout << "Country name is: " << territory->getCountryName() << endl;
				cout << "X: " << territory->getX() << " Y: " << territory->getY() << endl;
				cout << "Continent: " << territory->getContinent() << endl;
				cout << "Neighbor countries: ";
				//check neighbor countries
				string vectorNeighbor = territory->getNeighboringCountries().at(0)->getNeighboringCountries().at(0)->getCountryName();
				cout << endl << endl;

			}
		}
		//Checks for Map, Continent and Territories headers to validate map
		if (line.find("[Map]") != string::npos) {
			hasMap = true;
		}
		if (line.find("[Continents]") != string::npos) {
			hasContinents = true;
		}
		if (line.find("[Territories]") != string::npos && hasMap && hasContinents) {
			hasTerritories = true;
			
		}
	}
	//If no checks are passed, map is invalid.
	if (!hasMap && !hasContinents && !hasTerritories) {
		cout << "Invalid map.";
		exit(0);
	}

	//Check for number of countries
	cout << "Number of countries: " << m->getContainedCountries().size() << endl;
	//Check neighbors to check graph connectivity
	cout << "Enter a country to get its neighbors: ";
	string neighborCheck;
	cin >> neighborCheck;
	//Pulls neighbor countries from the actual neighboringCountries vector of that country
	vector<Country*> neighborCheckVector = m->getCountryFromMapByName(neighborCheck)->getNeighboringCountries();
		string s = neighborCheckVector.at(0)->getCountryName();
		cout << s << neighborCheckVector.size();

	inputfilestream.close();


}

/*int main() {
	MapLoader("World.map");
	system("pause");
	return 0;
}*/

