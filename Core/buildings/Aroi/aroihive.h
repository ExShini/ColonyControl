#ifndef AROIHIVE_H
#define AROIHIVE_H
#include "Core/buildings/building.h"
#include "Core/player/requestmanager.h"

enum MovingDirection
{
	DIR_UP = 0,
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_NUMBER
};

class AroiHive: public Building
{
public:
	AroiHive(GObjWrapper * wrapper, Sector *sector, int population, int initialStep, int plID);
	virtual ~AroiHive();

protected:
	virtual void process(int step);
	virtual void processHiveMigration();

	int m_migrationDirection;
};
#endif // AROIHIVE_H
