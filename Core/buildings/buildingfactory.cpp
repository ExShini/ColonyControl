#include "buildingfactory.h"

BuildingFactory::BuildingFactory(int playerID):
	m_playerID(playerID)
{

}

BuildingFactory::~BuildingFactory()
{

}

Building* BuildingFactory::buildStructure(OBJECT_TYPE type,
										  GObjWrapper *wrapper,
										  Sector *sector,
										  int population,
										  int initialStep)
{
	Q_UNUSED(type)
	Q_UNUSED(wrapper)
	Q_UNUSED(sector)
	Q_UNUSED(population)
	Q_UNUSED(initialStep)

	return nullptr;
}
