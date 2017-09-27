#include "Map.h"

class MapLoader {
public:
	MapLoader(std::string fileDirectory);
private:
	Map* map;
};