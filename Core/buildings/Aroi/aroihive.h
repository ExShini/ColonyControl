#ifndef AROIHIVE_H
#define AROIHIVE_H
#include "Core/buildings/building.h"
#include "Core/player/requestmanager.h"

class AroiHive: public Building
{
public:
	AroiHive(GObjWrapper * wrapper, Sector *sector, int population, int initialStep, int plID);
	virtual ~AroiHive();

protected:
	virtual void process(int step);
};
#endif // AROIHIVE_H
