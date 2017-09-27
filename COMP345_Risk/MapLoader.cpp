#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "MapLoader.h"
using namespace std;

MapLoader::MapLoader(std::string fileDirectory) {
	std::ifstream inputfilestream;
	inputfilestream.open(fileDirectory);

	std::string line;
	std::vector<std::string> listOfTerritories;
	bool recordingTerritories = false;

	while (std::getline(inputfilestream, line)) {
		if (recordingTerritories) {
			if (!line.empty()) {
				Country territory;
				listOfTerritories.push_back(line);
				stringstream ss(line);
				vector<string> lineVector;
				while (ss) {
					string substring;
					getline(ss, substring, ',');
					lineVector.push_back(substring);
				}
					territory.setCountryName(lineVector.at(0));
					territory.setX(stoi(lineVector.at(1)));
					territory.setY(stoi(lineVector.at(2)));
					territory.setContinent(lineVector.at(3));
					vector<Country*> neighborCountries;
					for (int i = 4; i < lineVector.size(); i++) {
						Country* country = new Country(lineVector[i]);
						territory.setNeighboringCountries(country);
					}
				
				cout << "Country name is: " << territory.getCountryName() << endl;
				cout << "X: " << territory.getX() << " Y: " << territory.getY() << endl;
				cout << "Continent: " << territory.getContinent() << endl;
				cout << "Neighbor countries: ";
				vector<Country*> vectorNeighbor = territory.getNeighboringCountries();
				for (int j = 0; j<vectorNeighbor.size(); j++) {
					cout << vectorNeighbor[j]->getCountryName() << " ";
				}
				cout << endl << endl;

			}
		}
		if (line.find("[Territories]") != std::string::npos) {
			recordingTerritories = true;
			
		}
	}
	inputfilestream.close();


}

int main() {
	MapLoader("World.map");
	system("pause");
	return 0;
}

