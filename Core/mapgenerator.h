#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include "Enums/map.h"


class Container
{
	int value[MAP_WIDTH][MAP_HEIGHT];
};

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	Map* generateMap();

private:

	void resetMapValues(Map* map);
	void generateMapLayer(MapContainer* cont, int maxValue, int minValue, int defaulValue, int shiftPer);
	int getRandValue(int maxValue, int minValue);
	int getShifting(int distanse, int maxValue, int shiftPer);

	int deamondStep(MapContainer *cont, int curX, int curY, int width, int maxValue, int minValue, int defaulValue, int shiftPer);

	void transformLayersToType(Map* map, MapContainer* height);

};

#endif // MAPGENERATOR_H
