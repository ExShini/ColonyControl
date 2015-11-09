#include "humanabilitymanager.h"
#include "Core/buildings/building.h"
#include "Abilities/ioncanonsatellite.h"
#include "Core/UnitController/unitcontroller.h"
#include "qdebug.h"

HumanAbilityManager::HumanAbilityManager(int playerID):
	AbilityManager(playerID)
{
}

void HumanAbilityManager::init()
{
	registerAbilityType(ION_CANON, 5000, 50000, 1, 10, 4);
	m_abilityExecuters[ION_CANON] = (AbilityExecutor*)
			UnitController::getInstance()->buildAbilityExecutor(m_playerID, t_HUMAN_ION_CANON_SATELLITE);
}

HumanAbilityManager::~HumanAbilityManager()
{
	// TODO
}

int HumanAbilityManager::abilityWasApplied(ABILITIES abilityType, Building *building)
{
	if(!m_abilityExecuters.keys().contains(abilityType))
	{
		qDebug() << "HumanAbilityManager::abilityWasApplied: Error! We have not such ability: " << abilityType;
		return INVALIDE_VALUE;
	}

	AbilityExecutor* executor = m_abilityExecuters[abilityType];

	if(abilityType == ION_CANON)
	{
		executor->activateAt(building);
	}

	int newCostForAbility = increaseCostFor(abilityType);

	return newCostForAbility;
}
