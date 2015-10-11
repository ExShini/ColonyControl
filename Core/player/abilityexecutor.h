#ifndef ABILITYEXECUTOR_H
#define ABILITYEXECUTOR_H
#include "Core/UnitController/Units/unit.h"

class AbilityExecutor: public Unit
{
public:
	AbilityExecutor(UnitWrapper *wrapper, OBJECT_TYPE type, int initialStep);
	virtual ~AbilityExecutor();
	virtual void process(int step);

	bool isFreeToUse()		{ return m_freeState; }
	virtual void activateAt(Building* building);

protected:
	bool m_freeState;
};

#endif // ABILITYEXECUTOR_H
