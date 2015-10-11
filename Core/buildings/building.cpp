#include "building.h"
#include "Core/gobjwrapper.h"
#include "Core/objectstatecontroller.h"


Building::Building(GObjWrapper *wrapper, Sector* sector, int initialStep, int plID):
	GObject(wrapper),
	m_sector(sector),
	m_initialStep(initialStep),
	m_level(0),
	m_maxLevel(0)
{    
	m_playerID = plID;
	m_player = PlayerController::getInstance()->getPlayer(m_playerID);
	setMapCoord(sector->getMapX(), sector->getMapY());
	m_wrapper->setMarker(m_playerID);
}

Building::~Building()
{

}


void Building::process(int step)
{
	Q_UNUSED(step)
}

void Building::checkState()
{
	int infrostructure = getResources(INFROSTRUCTURE);
	int topInfLevel = getResLimit(INFROSTRUCTURE);
	int lowInfLevel = m_player->getResLimit(m_type, INFROSTRUCTURE, m_level);
	int currentLevel = m_level;

	// check to increae level
	if(infrostructure >= topInfLevel && m_level < m_maxLevel)
	{
		m_level++;
	}
	// chack to degrise level
	else if(infrostructure < lowInfLevel && m_level > 0)
	{
		m_level--;
	}

	if(currentLevel != m_level)
	{
		RESOURSES resType;
		Resourse value;

		GObject::resetIteration();

		while(this->getNextResource(resType, value))
		{
			if(resType != INFROSTRUCTURE)
			{
				setResLimit(resType, m_player->getResLimit(m_type, resType, m_level));
			}
			else
			{
				setResLimit(resType, m_player->getResLimit(m_type, resType, m_level + 1));
			}
		}

		m_wrapper->setLevel(m_level);
	}
}

void Building::deactivate()
{
	if(m_wrapper != nullptr)
	{
		m_wrapper->setMarker(INVALIDE_VALUE);
	}

	GObject::deactivate();
}

void Building::activate()
{
	m_wrapper->setEnabled();
	m_wrapper->setLevel(0);
	m_wrapper->setType(m_type);
}

/************************************************
 * Func: removeWrapper
 * Desc: Remove wrapper from building.
 * Note: Used for updating process to save wrapper active
 *		 Also we should disable this object
 ***********************************************/
void Building::removeWrapper()
{
	ObjectStateController::getInstance()->setBuildingCondition(m_id, DESTROED_CONDITION);
	m_active = false;
	m_wrapper = nullptr;
}

/************************************************
 * Func: takeDamage
 * Desc: Building take demage
 ***********************************************/
void Building::takeDamage(int damage)
{
	int infrStruct = getResources(INFROSTRUCTURE);
	int population = getResources(POPULATION);

	population -= damage;
	if(population < 0)
	{
		population = 0;
	}

	infrStruct -= (damage / 2);
	if(infrStruct < 0)
	{
		infrStruct = 0;
		ObjectStateController::getInstance()->setBuildingCondition(m_id, DESTROED_CONDITION);
	}

	setResources(INFROSTRUCTURE, infrStruct);
	setResources(POPULATION, population);
}
