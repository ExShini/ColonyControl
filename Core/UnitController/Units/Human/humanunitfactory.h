#ifndef HUMANUNITFACTORY_H
#define HUMANUNITFACTORY_H
#include "../unitfactory.h"

class HumanUnitFactory: public UnitFactory
{
public:
	HumanUnitFactory(int playerID);
	virtual ~HumanUnitFactory();
	virtual Unit* buildUnit(OBJECT_TYPE unitType, Building* base, UnitWrapper* wrapper);
};

#endif // HUMANUNITFACTORY_H
