#ifndef AROIABILITYMANAGER_H
#define AROIABILITYMANAGER_H
#include "../abilitymanager.h"

class AroiAbilityManager: public AbilityManager
{
public:
	AroiAbilityManager(int playerID);
	virtual ~AroiAbilityManager();
	virtual void init();
	virtual int abilityWasApplied(ABILITIES abilityType, Building* building);

};

#endif // AROIABILITYMANAGER_H
