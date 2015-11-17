#include "aroihive.h"
#include "Core/player/player.h"
#include "Core/gobjwrapper.h"
#include "Enums/objects.h"
#include "Enums/gameprocessingsettings.h"
#include "Core/randomgen.h"
#include "Core/objectcontroller.h"
#include "Core/goalgorithms.h"

#include "qdebug.h"


/*************************************
FUNC: AroiHive(...)
DESC: constructor
*************************************/
AroiHive::AroiHive(GObjWrapper *wrapper, Sector* sector, int population, int initialStep, int plID):
	Building(wrapper, sector, initialStep, plID)
{
	m_type = t_AROI_HIVE;
	m_level = 1;

	m_wrapper->setType(m_type);
	m_wrapper->setLevel(m_level, UI_NORMAL);
	m_wrapper->setEnabled();

	regResourse(POPULATION);
	setResources(POPULATION, population);

	regResourse(SUPPLY);

	regResourse(INFROSTRUCTURE);

	m_maxLevel = AROI_MAX_HIVE_LEVEL;
	m_migrationDirection = RandomGen::getRand() % DIR_NUMBER;
}

/*************************************
FUNC: ~AroiHive()
DESC: destructor
*************************************/
AroiHive::~AroiHive()
{

}

/*************************************
FUNC: process()
DESC: main process function
*************************************/
void AroiHive::process(int step)
{

	if(step != m_initialStep)
		return;

	Building::process(step);

	// process it 1 time in 5 sec
	// we just reuse m_stateCount
	if(m_stateCount == 0)
	{
		processHiveMigration();
	}

	int population = getResources(POPULATION);

	// update main resource
	int mainResChange = HUMANS_GROPS(population);
	m_player->changeMainResValue(mainResChange);
}


/*************************************
FUNC: processHiveMigration()
DESC: population from hive can migrate to nearest sectors and create
	  new hive or invite in another
*************************************/
void AroiHive::processHiveMigration()
{
	Request* populationReq = getRequest(POPULATION);

	if(populationReq == nullptr)
	{
		// we have not some request for population at this moment - just return
		return;
	}

	if(populationReq->type != PROVIDE || !populationReq->registred)
	{
		// we can't provide some population, we wait it from other hive
		return;
	}

	int mapX = getMapX();
	int mapY = getMapY();

	// determine coordinates for migrating by direction
	switch (m_migrationDirection)
	{
	case DIR_UP:
		mapY--;
		break;
	case DIR_LEFT:
		mapX--;
		break;
	case DIR_DOWN:
		mapY++;
		break;
	case DIR_RIGHT:
		mapX++;
		break;
	default:
		break;
	}

	int populationToSend = populationReq->value;
	Building* building = ObjectController::getInstance()->getBuilding(mapX, mapY);


	if(building != nullptr)
	{
		// if we found building - try to migrate to this building
		if(building->getPlayerID() == getPlayerID())
		{
			GOAlgorithms::transferResourceByRequest(this, building, POPULATION);
		}
	}
	else
	{
		// try to capture this area
		Building* building = ObjectController::getInstance()
				->buildObj(t_AROI_HIVE, mapX, mapY, populationToSend, m_playerID);

		if(building != nullptr)
		{
			int newOurPopulation = getResources(POPULATION) - populationToSend;
			setResources(POPULATION, newOurPopulation);

			// delete populationReq, by the reason that it is complite
			delete populationReq;
			requestComplited(POPULATION);
		}
	}

	m_migrationDirection++;
	if(m_migrationDirection >= DIR_NUMBER)
	{
		m_migrationDirection = 0; // DIR_UP
	}
}
