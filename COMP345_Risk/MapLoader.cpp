#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "MapLoader.h"
#include <algorithm>
using namespace std;

MapLoader::MapLoader(std::string fileDirectory) {
	std::ifstream inputfilestream;
	inputfilestream.open(fileDirectory);

	std::string line;
	bool recordingTerritories = false;
	Map* m = new Map();
	while (std::getline(inputfilestream, line)) {
		if (recordingTerritories) {
			if (!line.empty()) {
				Country* territory = new Country();
				stringstream ss(line);
				std::string word;
				vector<string> lineVector;
				while (std::getline(ss, word, ',')) {
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
						m->setContainedCountries(neighboringCountry);
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
		if (line.find("[Territories]") != std::string::npos) {
			recordingTerritories = true;
			
		}
	}
	cout << "Number of countries: " << m->getContainedCountries().size();
	//cout << "Neighbor check: " << m->getCountryFromMapByName("Alaska")->getNeighboringCountries.at(0)->getCountryName();
	inputfilestream.close();


}

/*int main() {
	MapLoader("World.map");
	system("pause");
	return 0;
}*/

