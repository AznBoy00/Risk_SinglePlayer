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
		if (hasTerritories) {
			if (!line.empty()) {
				Country* territory = new Country();
				stringstream ss(line);
				string word;
				vector<string> lineVector;
				while (getline(ss, word, ',')) {
					lineVector.push_back(word);
				}
				territory->setCountryName(lineVector.at(0));
				territory->setX(stoi(lineVector.at(1)));
				territory->setY(stoi(lineVector.at(2)));
				territory->setContinent(lineVector.at(3));
				m->setContainedCountries(territory);

				for (int i = 4; i < lineVector.size(); i++) {
					if (m->containsCountry(lineVector[i]) == false) {
						//cout << "this country is new";
						Country* neighboringCountry = new Country(lineVector.at(i));
						//m->setContainedCountries(neighboringCountry);
						territory->setNeighboringCountries(neighboringCountry);
					}
					else{
						//cout << "this country is not new";
						territory->setNeighboringCountries(m->getCountryFromMapByName(lineVector[i]));
					}
				}
				
				cout << "Country name is: " << territory->getCountryName() << endl;
				cout << "X: " << territory->getX() << " Y: " << territory->getY() << endl;
				cout << "Continent: " << territory->getContinent() << endl;
				cout << "Neighbor countries: ";
				vector<Country*> vectorNeighbor = territory->getNeighboringCountries();
				for (int j = 0; j<vectorNeighbor.size(); j++) {
					cout << vectorNeighbor[j]->getCountryName() << ", ";
				}
				cout << endl << endl;

			}
		}
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
	if (!hasMap && !hasContinents && !hasTerritories) {
		cout << "Invalid map.";
	}

	cout << "Number of countries: " << m->getContainedCountries().size() << endl;
	cout << "Enter a country to get its neighbors: ";
	string neighborCheck;
	cin >> neighborCheck;
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

