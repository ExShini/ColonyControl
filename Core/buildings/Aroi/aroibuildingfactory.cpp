#include "aroibuildingfactory.h"
#include "QDebug"

AroiBuildingFactory::AroiBuildingFactory(int playerID):
	BuildingFactory(playerID)
{

}

AroiBuildingFactory::~AroiBuildingFactory()
{

}

Building* AroiBuildingFactory::buildStructure(OBJECT_TYPE type,
											   GObjWrapper *wrapper,
											   Sector *sector,
											   int population,
											   int initialStep)
{
	Q_UNUSED(wrapper)
	Q_UNUSED(sector)
	Q_UNUSED(population)
	Q_UNUSED(initialStep)

	Building* building = nullptr;

	switch (type) {

	case t_AROI_HIVE:
		//building = new HumSettlers(wrapper, sector, population, initialStep, m_playerID);
		break;
	default:
		qDebug() << "HumanBuildingFactory::buildStructure: Error! Wrong type : " << type;
		break;
	}

	return building;
}
