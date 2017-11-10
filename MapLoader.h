#pragma once
#include "Map.h"

class MapLoader {
public:
	MapLoader(std::string fileDirectory);
	Map* getMap();
private:
	Map* map;
};