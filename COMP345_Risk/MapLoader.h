#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Map.h";

class MapLoader {
public:
    MapLoader(std::string directory);
private:
	Map* map;
};

#endif 

