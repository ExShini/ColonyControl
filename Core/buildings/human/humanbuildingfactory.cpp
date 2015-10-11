#include "humanbuildingfactory.h"
#include "QDebug"

#include "humcolonycenter.h"
#include "humsettlers.h"
#include "humtransportcenter.h"

HumanBuildingFactory::HumanBuildingFactory(int playerID):
	BuildingFactory(playerID)
{

}

HumanBuildingFactory::~HumanBuildingFactory()
{

}

Building* HumanBuildingFactory::buildStructure(OBJECT_TYPE type,
											   GObjWrapper *wrapper,
											   Sector *sector,
											   int population,
											   int initialStep)
{
	Building* building = nullptr;

	switch (type) {

	case t_HUMAN_SETTLERS:
		building = new HumSettlers(wrapper, sector, population, initialStep, m_playerID);
		break;

	case t_HUMAN_COLONY_CENTER:
		building = new HumColonyCenter(wrapper, sector, population, initialStep, m_playerID);
		break;
	case t_HUMAN_TRANSPORT_CENTER:
		building = new HumTransportCenter(wrapper, sector, population, initialStep, m_playerID);
		break;
	default:
		qDebug() << "HumanBuildingFactory::buildStructure: Error! Wrong type : " << type;
		break;
	}

	return building;
}
