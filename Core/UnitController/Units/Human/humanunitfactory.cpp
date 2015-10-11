#include "humanunitfactory.h"
#include "humshuttle.h"
#include "Core/player/Human/Abilities/ioncanonsatellite.h"
#include "Core/player/Human/Abilities/ioncanonbullet.h"

HumanUnitFactory::HumanUnitFactory(int playerID):
	UnitFactory(playerID)
{

}

HumanUnitFactory::~HumanUnitFactory()
{

}

Unit* HumanUnitFactory::buildUnit(OBJECT_TYPE unitType, Building *base, UnitWrapper *wrapper)
{
	Unit* unit = nullptr;
	int initStep = getInitStep();

	switch (unitType) {
	case t_HUMAN_SHUTTLE:
	{
		unit = new HumShuttle(wrapper, base, initStep);
	}
		break;
	case t_HUMAN_ION_CANON_SATELLITE:
	{
		unit = new IonCanonSatellite(wrapper, initStep, m_playerID);
	}
		break;
	case t_HUMAN_ION_CANON_BULLET:
	{
		unit = new IonCanonBullet(wrapper, initStep);
	}
		break;
	default:
		break;
	}

	return unit;
}

