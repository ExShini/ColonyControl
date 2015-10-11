#include "unitfactory.h"
#include "Enums/coresettings.h"

UnitFactory::UnitFactory(int playerID):
	m_playerID(playerID),
	m_initStep(0)
{

}

UnitFactory::~UnitFactory()
{

}

Unit* UnitFactory::buildUnit(OBJECT_TYPE unitType, Building *base, UnitWrapper* wrapper)
{
	Q_UNUSED(unitType)
	Q_UNUSED(base)
	Q_UNUSED(wrapper)
	return nullptr;
}

int UnitFactory::getInitStep()
{
	m_initStep++;

	if(m_initStep >= GAME_STEP_PER_SECOND)
		m_initStep = 0;

	return m_initStep;
}
