#ifndef UNITFACTORY_H
#define UNITFACTORY_H
#include "Enums/objects.h"
#include "Core/buildings/building.h"
#include "unit.h"

class UnitFactory
{
public:
	UnitFactory(int playerID);
	virtual ~UnitFactory();
	virtual Unit* buildUnit(OBJECT_TYPE unitType, Building* base, UnitWrapper* wrapper);

protected:
	int getInitStep();

	int m_playerID;
	int m_initStep;
};

#endif // UNITFACTORY_H
