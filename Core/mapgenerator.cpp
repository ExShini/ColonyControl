#include "mapgenerator.h"
#include "randomgen.h"
#include "Enums/objects.h"
#include "qdebug.h"

/************************************************
 * Func: MapGenerator
 * Desc: constructor
 ***********************************************/
MapGenerator::MapGenerator()
{

}

/************************************************
 * Func: ~MapGenerator
 * Desc: destructor
 ***********************************************/
MapGenerator::~MapGenerator()
{

}


/************************************************
 * Func: generateMap
 * Desc: Main generator function
 ***********************************************/
Map* MapGenerator::generateMap()
{
	Map* map = new Map();

	resetMapValues(map);

	generateMapLayer(&(map->fertility),
					 MAX_FERTILITY,
					 MIN_FERTILYTY,
					 DEF_FERTILYTY,
					 FERTILYTY_SHIFTING_PERSENTS);

	generateMapLayer(&(map->mineralWealth),
					 MAX_MINERAL_WEALTH,
					 MIN_MINERAL_WEALTH,
					 DEF_MINERAL_WEALTH,
					 MINERAL_WEALTH_SHIFTING_PERSENTS);

	MapContainer * heights = new MapContainer();
	generateMapLayer(heights,
					 MAX_FIELD_HEIGHT,
					 MIN_FIELD_HEIGHT,
					 DEF_FIELD_HEIGHT,
					 FIELD_HEIGHT_SHIFTING_PERSENTS);

	transformLayersToType(map, heights);

	return map;
}

/************************************************
 * Func: transformLayersToType
 * Desc: Convert generated values to sector's types
 ***********************************************/
void MapGenerator::transformLayersToType(Map *map, MapContainer *height)
{
	for(int x = 0; x < MAP_WIDTH; x++)
	{
		for(int y = 0; y < MAP_HEIGHT; y++)
		{
			//mount check
			if(height->value[x][y] >= MOUNT_MIN_HEIGHT)
			{
				map->type.value[x][y] = t_MOUNT;
			}
			else if(height->value[x][y] <= DEEP_LAVA_HEIGHT)
			{
				map->type.value[x][y] = t_DEEP_LAVA;
			}
			else if(height->value[x][y] <= LAVA_HEIGHT_LEVEL)
			{
				map->type.value[x][y] = t_LAVA;
			}
			else if(map->mineralWealth.value[x][y] >= MINERAL_REACH_FIELD)
			{
				map->type.value[x][y] = t_MINERAL_FIELD;
			}
			else if(map->fertility.value[x][y] >= FERTILYTY_REACH_FIELD)
			{
				map->type.value[x][y] = t_FERTILYTY_FIELD;
			}
			else
			{
				map->type.value[x][y] = t_DESERT;
			}
		}
	}
}

/************************************************
 * Func: resetMapValues
 * Desc: reset values for map container
 ***********************************************/
void MapGenerator::resetMapValues(Map *map)
{
	for(int i = 0; i < MAP_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			map->fertility.value[i][j] = DEF_MAP_VALUES;
			map->mineralWealth.value[i][j] = DEF_MAP_VALUES;
			map->type.value[i][j] = DEF_MAP_VALUES;
		}
	}
}

/************************************************
 * Func: generateMapLayer
 * Desc: generate separate map's layout
 * It used for all: resourses, map's heights and so on
 ***********************************************/
void MapGenerator::generateMapLayer(MapContainer *cont,
									int maxValue,
									int minValue,
									int defaulValue,
									int shiftPer)
{
	//check settings
	if((!MAP_HEIGHT % 2 == 1) || (!MAP_WIDTH % 2 == 1))
	{
		qDebug() << "MapGenerator::generateMapLayer: incorrect map sizes";
	}

	//local members
	int width = MAP_WIDTH;	// square width
	int curX = 0;
	int curY = 0;
	int x, y;	// coordinate of current point (which culculeted at this moment)
	int sum = 0;	// used for summ culculating
	int resVal = 0;

	bool culculating = true;	// flag - process while it true

	//init first 4 points
	cont->value[0][0] = getRandValue(maxValue, minValue);
	cont->value[MAP_WIDTH - 1][0] = getRandValue(maxValue, minValue);
	cont->value[0][MAP_HEIGHT - 1] = getRandValue(maxValue, minValue);
	cont->value[MAP_WIDTH - 1][MAP_HEIGHT - 1] = getRandValue(maxValue, minValue);

	while (culculating)
	{
		// square step
		for( curX = 0 ; (curX + width - 1) < MAP_WIDTH ; curX +=  width - 1 )
		{
			for ( curY = 0 ; (curY + width - 1) < MAP_HEIGHT ; curY +=  width - 1 )
			{
				//culc center point
				x = curX +(width / 2);	// x = curX +(width / 2) + 1 - 1;
				y = curY +(width / 2);

				//culculate sum of main points
				sum = cont->value[curX][curY] +
						cont->value[curX + width - 1][curY] +
						cont->value[curX][curY + width - 1] +
						cont->value[curX + width - 1][curY + width - 1];

				resVal = (sum / 4) + getShifting((width / 2) * 1.41, maxValue, shiftPer);

				if(resVal > maxValue)
					resVal = maxValue - (resVal - maxValue);
				else if(resVal < minValue)
					resVal = minValue + (minValue - resVal);

				cont->value[x][y] = resVal;


			}
		}


		// diamond step
		for( curX = 0 ; (curX + width - 1) < MAP_WIDTH ; curX +=  width - 1 )
		{
			for ( curY = 0 ; (curY + width - 1) < MAP_HEIGHT ; curY +=  width - 1 )
			{
				//left border
				x = curX;
				y = curY +(width / 2);

				cont->value[x][y] = deamondStep(cont, x, y, width, maxValue, minValue, defaulValue, shiftPer);

				//right border
				x = curX + width - 1;
				y = curY + (width / 2);

				cont->value[x][y] = deamondStep(cont, x, y, width, maxValue, minValue, defaulValue, shiftPer);

				//top border
				x = curX + (width / 2);
				y = curY;

				cont->value[x][y] = deamondStep(cont, x, y, width, maxValue, minValue, defaulValue, shiftPer);

				//bottom border
				x = curX + (width / 2);
				y = curY + width - 1;

				cont->value[x][y] = deamondStep(cont, x, y, width, maxValue, minValue, defaulValue, shiftPer);
			}
		}

		width = (width / 2) + 1;

		if(width == 2)
			culculating = false;
	}
}

/************************************************
 * Func: deamondStep
 * Desc: deamond step of generation for curren cell (x,y positions)
 ***********************************************/
int MapGenerator::deamondStep(MapContainer* cont,
							  int curX,
							  int curY,
							  int width,
							  int maxValue,
							  int minValue,
							  int defaulValue,
							  int shiftPer)
{
	int sum = 0;

	// top point
	if((curY - (width / 2)) >= 0)
	{
		sum += cont->value[curX][curY - (width / 2)];
	}
	else
	{
		sum += defaulValue;
	}

	// bottom point
	if((curY + (width / 2)) < MAP_HEIGHT)
	{
		sum += cont->value[curX][curY + (width / 2)];
	}
	else
	{
		sum += defaulValue;
	}

	// left point
	if((curX - (width / 2)) >= 0)
	{
		sum += cont->value[curX - (width / 2)][curY];
	}
	else
	{
		sum += defaulValue;
	}


	// right point
	if((curX + (width / 2)) < MAP_WIDTH)
	{
		sum += cont->value[curX + (width / 2)][curY];
	}
	else
	{
		sum += defaulValue;
	}

	int resVal = (sum / 4) + getShifting(width / 2, maxValue, shiftPer);

	if(resVal > maxValue)
		resVal = maxValue - (resVal - maxValue);
	else if(resVal < minValue)
		resVal = minValue + (minValue - resVal);


	return resVal;
}

/************************************************
 * Func: getRandValue
 * Desc: provide random value with maxValue and minValue limits
 ***********************************************/
int MapGenerator::getRandValue(int maxValue, int minValue)
{
	int res = minValue;
	int range = maxValue - minValue;

	if(range != 0)
	{
		// add random part
		res += (RandomGen::getRand() % (maxValue - minValue));
	}

	return res;
}

/************************************************
 * Func: getShifting
 * Desc: provide random shifting.
 * It used for noise generating
 ***********************************************/
int MapGenerator::getShifting(int distanse, int maxValue, int shiftPer)
{
	int randNumber = RandomGen::getRand();
	int resVal = 0;
	int shifting = getRandValue(GET_MAX_SHIFT(distanse, maxValue, shiftPer), 0);
	shifting = shifting % maxValue;

	if(randNumber % 2 == 1)
	{
		resVal = shifting;
	}
	else
	{
		resVal = -shifting;
	}

	return resVal;
}
