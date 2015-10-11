#ifndef EMPTYSECTORRADAR_H
#define EMPTYSECTORRADAR_H
#include "qlist.h"
#include "Enums/mapsettings.h"

class ObjectController;
class Sector;

enum SectorStatus
{
	NO_STATUS = 0,
	NOT_APPLICABLE,
	BUILDED,
	EMPTY
};

struct Point
{
	int x;
	int y;
	SectorStatus status;
};



class EmptySectorRadar
{
public:
	EmptySectorRadar(int x, int y, int plID);
	~EmptySectorRadar();
	void setSetting(int radius, int rate);
	void scan();
	QList<Sector*>* getResults();


protected:
	void cleanMap();
	void scanPoint(Point* point);
	void scanSector(int x, int y);

	int m_x;
	int m_y;
	int m_playerID;

	int m_radius;
	int m_rate;
	int m_currPhase;

	Point* m_map[MAP_WIDTH][MAP_HEIGHT];

	QList<Point*> m_processList;
	QList<Sector*> m_emptySectorsList;
	ObjectController* m_objCntr;
};

#endif // EMPTYSECTORRADAR_H
