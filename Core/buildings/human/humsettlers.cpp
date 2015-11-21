#include "humsettlers.h"
#include "Core/player/player.h"
#include "Core/gobjwrapper.h"
#include "Enums/objects.h"
#include "Enums/gameprocessingsettings.h"

#include "qdebug.h"

/*************************************
FUNC: HumSettlers(...)
DESC: constructor
*************************************/
HumSettlers::HumSettlers(GObjWrapper *wrapper, Sector* sector, int population, int initialStep, int plID):
	Building(wrapper, sector, initialStep, plID)
{
	m_type = t_HUMAN_SETTLERS;

	m_wrapper->setType(m_type);
	m_wrapper->setLevel(m_level, UI_NORMAL);
	m_wrapper->setEnabled();

	regResourse(POPULATION);
	setResources(POPULATION, population);

	regResourse(SUPPLY);

	regResourse(INFROSTRUCTURE);

	m_maxLevel = HUMAN_MAX_SETTLEMENT_LEVEL;
}

/*************************************
FUNC: ~HumSettlers()
DESC: destructor
*************************************/
HumSettlers::~HumSettlers()
{

}

/*************************************
FUNC: process()
DESC: main process function
*************************************/
void HumSettlers::process(int step)
{

	if(step != m_initialStep)
		return;

	Building::process(step);


	Resourse* res = getResourcesObj(POPULATION);
	int population = res->value;

	// update main resource
	int mainResChange = POPULATION_GROPS(population, res->sizeOfGroup);
	m_player->changeMainResValue(mainResChange);
}
