#ifndef HUMANABILITYMANAGER_H
#define HUMANABILITYMANAGER_H
#include "../abilitymanager.h"
#include "../abilityexecutor.h"
#include "QMap"

class HumanAbilityManager: public AbilityManager
{
public:
	HumanAbilityManager(int playerID);
	virtual ~HumanAbilityManager();
	virtual void init();
	virtual int abilityWasApplied(ABILITIES abilityType, Building* building);

protected:
	QMap<ABILITIES, AbilityExecutor*> m_abilityExecuters;
};

#endif // HUMANABILITYMANAGER_H
