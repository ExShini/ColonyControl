#include "aroihive.h"
#include "Core/player/player.h"
#include "Core/gobjwrapper.h"
#include "Enums/objects.h"
#include "Enums/gameprocessingsettings.h"

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


	int population = getResources(POPULATION);

	// update main resource
	int mainResChange = HUMANS_GROPS(population);
	m_player->changeMainResValue(mainResChange);
}
