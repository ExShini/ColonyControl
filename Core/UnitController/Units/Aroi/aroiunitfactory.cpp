#include "aroiunitfactory.h"
AroiUnitFactory::AroiUnitFactory(int playerID):
	UnitFactory(playerID)
{

}

AroiUnitFactory::~AroiUnitFactory()
{

}

Unit* AroiUnitFactory::buildUnit(OBJECT_TYPE unitType, Building *base, UnitWrapper *wrapper)
{
	// TODO
	Unit* unit = nullptr;
	int initStep = getInitStep();

	Q_UNUSED(initStep)
	Q_UNUSED(unitType)
	Q_UNUSED(base)
	Q_UNUSED(wrapper)

	return unit;
}

