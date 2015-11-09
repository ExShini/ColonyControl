#ifndef HUMANABILITYMANAGER_H
#define HUMANABILITYMANAGER_H
#include "../abilitymanager.h"

class HumanAbilityManager: public AbilityManager
{
public:
	HumanAbilityManager(int playerID);
	virtual ~HumanAbilityManager();
	virtual void init();
	virtual int abilityWasApplied(ABILITIES abilityType, Building* building);

};

#endif // HUMANABILITYMANAGER_H
