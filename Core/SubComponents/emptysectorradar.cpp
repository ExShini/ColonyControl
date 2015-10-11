#include "emptysectorradar.h"
#include "Core/objectcontroller.h"
#include "qdebug.h"
#include "cmath"

EmptySectorRadar::EmptySectorRadar(int x, int y, int plID):
	m_x(x),
	m_y(y),
	m_playerID(plID),
	m_radius(0),
	m_rate(0),
	m_currPhase(0),
	m_map()
{
	m_objCntr = ObjectController::getInstance();

	for(int i = 0; i < MAP_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			m_map[i][j] = new Point();
			m_map[i][j]->x = i;
			m_map[i][j]->y = j;
		}
	}
}

EmptySectorRadar::~EmptySectorRadar()
{
}

void EmptySectorRadar::setSetting(int radius, int rate)
{
	m_radius = radius;
	m_rate = rate;
}

void EmptySectorRadar::scan()
{
	cleanMap();

	m_currPhase++;
	if(m_currPhase >= m_rate)
	{
		m_currPhase = 0;
	}

	if(m_currPhase != 0)
	{
		return;
	}

	bool process = true;

	//add center point to process map
	Point* center = m_map[m_x][m_y];
	m_processList.push_back(center);


	while (process)
	{
		Point* currPoint = m_processList.front();
		m_processList.pop_front();

		scanPoint(currPoint);

		if(m_processList.isEmpty())
		{
			process = false;
		}
	}
}

void EmptySectorRadar::scanPoint(Point *point)
{
	if(point == nullptr)
	{
		qDebug() << "EmptySectorRadar::scanPoint : Error! point is null!";
		return;
	}

	int x = point->x;
	int y = point->y;

	scanSector(x + 1, y);
	scanSector(x - 1, y);
	scanSector(x + 1, y + 1);
	scanSector(x + 1, y - 1);
	scanSector(x, y + 1);
	scanSector(x, y - 1);
	scanSector(x - 1, y + 1);
	scanSector(x - 1, y - 1);
}

void EmptySectorRadar::scanSector(int x, int y)
{
	// check range
	int range = abs(m_x - x) + abs(m_y - y);
	if(range > m_radius)
	{
		return;
	}

	if(x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT)
	{
		if(m_map[x][y]->status != NO_STATUS)
		{
			return;
		}

		Sector* sec = m_objCntr->getSector(x, y);

		if(sec->itApplicable())
		{
			Building* building = nullptr;
			building = m_objCntr->getBuilding(x, y);

			if(building != nullptr)
			{
				m_map[x][y]->status = BUILDED;
				if(building->getPlayerID() == m_playerID)
				{
					m_processList.push_back(m_map[x][y]);
				}
			}
			else
			{
				m_map[x][y]->status = EMPTY;
				m_emptySectorsList.push_back(sec);
			}
		}
		else
		{
			m_map[x][y]->status = NOT_APPLICABLE;
		}
	}
}

QList<Sector*>* EmptySectorRadar::getResults()
{
	return &m_emptySectorsList;
}

void EmptySectorRadar::cleanMap()
{
	m_emptySectorsList.clear();
	m_processList.clear();

	for(int i = 0; i < MAP_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			m_map[i][j]->status = NO_STATUS;
		}
	}
}
