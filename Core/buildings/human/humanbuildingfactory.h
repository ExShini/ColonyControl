#ifndef HUMANBUILDINGFACTORY_H
#define HUMANBUILDINGFACTORY_H
#include "../buildingfactory.h"

class HumanBuildingFactory : public BuildingFactory
{
public:
	HumanBuildingFactory(int playerID);
	virtual ~HumanBuildingFactory();

	virtual Building* buildStructure(OBJECT_TYPE type, GObjWrapper * wrapper, Sector *sector, int population, int initialStep);
};

#endif // HUMANBUILDINGFACTORY_H
