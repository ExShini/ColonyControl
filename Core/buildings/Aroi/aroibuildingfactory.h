#ifndef AROIBUILDINGFACTORY_H
#define AROIBUILDINGFACTORY_H
#include "../buildingfactory.h"

class AroiBuildingFactory : public BuildingFactory
{
public:
	AroiBuildingFactory(int playerID);
	virtual ~AroiBuildingFactory();

	virtual Building* buildStructure(OBJECT_TYPE type, GObjWrapper * wrapper, Sector *sector, int population, int initialStep);
};


#endif // AROIBUILDINGFACTORY_H
