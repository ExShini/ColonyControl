#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H
#include "Core/buildings/building.h"

class BuildingFactory
{
public:
	BuildingFactory(int playerID);
	virtual ~BuildingFactory();

	virtual Building* buildStructure(OBJECT_TYPE type, GObjWrapper * wrapper, Sector *sector, int population, int initialStep);

protected:
	int m_playerID;
};

#endif // BUILDINGFACTORY_H
