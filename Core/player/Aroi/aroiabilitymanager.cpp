#include "aroiabilitymanager.h"
#include "Core/buildings/building.h"
#include "Core/UnitController/unitcontroller.h"
#include "qdebug.h"

AroiAbilityManager::AroiAbilityManager(int playerID):
	AbilityManager(playerID)
{
}

void AroiAbilityManager::init()
{
}

AroiAbilityManager::~AroiAbilityManager()
{
	// TODO
}

int AroiAbilityManager::abilityWasApplied(ABILITIES abilityType, Building *building)
{
	if(!m_abilityExecuters.keys().contains(abilityType))
	{
		qDebug() << "HumanAbilityManager::abilityWasApplied: Error! We have not such ability: " << abilityType;
		return INVALIDE_VALUE;
	}

	AbilityExecutor* executor = m_abilityExecuters[abilityType];

//	if(abilityType == ION_CANON)
//	{
//		executor->activateAt(building);
//	}

//	int newCostForAbility = increaseCostFor(abilityType);

//	return newCostForAbility;

	return INVALIDE_VALUE;
}
