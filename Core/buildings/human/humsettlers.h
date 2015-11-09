#ifndef HUMSETTLERS_H
#define HUMSETTLERS_H
#include "Core/buildings/building.h"
#include "Core/player/requestmanager.h"

class HumSettlers: public Building
{
public:
	HumSettlers(GObjWrapper * wrapper, Sector *sector, int population, int initialStep, int plID);
	virtual ~HumSettlers();

protected:
	virtual void process(int step);
};

#endif // HUMSETTLERS_H
