#ifndef MAP
#define MAP
#include "mapsettings.h"

#define DEF_MAP_VALUES -1000
#define GET_MAX_SHIFT(dist, maxVal, shiftPer)((dist * maxVal * shiftPer) / 100)

#define MAX_FERTILITY 12000
#define MIN_FERTILYTY 200
#define DEF_FERTILYTY 500
#define FERTILYTY_SHIFTING_PERSENTS 5

#define MAX_MINERAL_WEALTH 2500
#define MIN_MINERAL_WEALTH 20
#define DEF_MINERAL_WEALTH 0
#define MINERAL_WEALTH_SHIFTING_PERSENTS 5

#define MAX_FIELD_HEIGHT 100
#define MIN_FIELD_HEIGHT 0
#define DEF_FIELD_HEIGHT 50
#define FIELD_HEIGHT_SHIFTING_PERSENTS 10

#define MOUNT_MIN_HEIGHT 80
#define LAVA_HEIGHT_LEVEL 20
#define DEEP_LAVA_HEIGHT 10
#define MINERAL_REACH_FIELD ((MAX_MINERAL_WEALTH * 80) / 100)
#define FERTILYTY_REACH_FIELD ((MAX_FERTILITY * 50) / 100)

struct MapContainer
{
	int value[MAP_WIDTH][MAP_HEIGHT];
};

struct Map
{
	MapContainer type;
	MapContainer fertility;
	MapContainer mineralWealth;
};

#endif // MAP

