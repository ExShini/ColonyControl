#ifndef AROIUNITFACTORY_H
#define AROIUNITFACTORY_H
#include "../unitfactory.h"

class AroiUnitFactory: public UnitFactory
{
public:
	AroiUnitFactory(int playerID);
	virtual ~AroiUnitFactory();
	virtual Unit* buildUnit(OBJECT_TYPE unitType, Building* base, UnitWrapper* wrapper);
};

#endif // AROIUNITFACTORY_H
