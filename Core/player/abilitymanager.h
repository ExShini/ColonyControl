#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H
#include "Enums/procsettings/ability.h"
#include "QMap"

class Building;

struct AbilitySettings
{
	int minCost;
	int maxCost;
	int currCost;
	int selfRecharge;
	int fullRechargeWork;
	int currentRechargeWorks;
	int costOfApply;
};


class AbilityManager
{
public:
	AbilityManager(int playerID);
	virtual ~AbilityManager();
	virtual void init();
	virtual int getCostOf(ABILITIES abilityType);
	virtual int abilityWasApplied(ABILITIES abilityType, Building *building);
	virtual void refreshAbilities();

protected:
	void registerAbilityType(ABILITIES type,
							 int minCost,
							 int maxCost,
							 int selfRecharge,
							 int maxRechargeWorks,
							 int costOfApply);

	int increaseCostFor(ABILITIES type);
	int getCostFor(AbilitySettings* abilitySett);

	QMap<ABILITIES, AbilitySettings*> m_abilityConfigs;
	int m_playerID;
};

#endif // ABILITYMANAGER_H
