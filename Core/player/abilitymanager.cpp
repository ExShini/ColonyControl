#include "abilitymanager.h"
#include "Enums/objects.h"
#include "Core/buildings/building.h"
#include "UIDrawer/UIElements/abilitymenucontroller.h"
#include "qdebug.h"

AbilityManager::AbilityManager(int playerID):
	m_abilityConfigs(),
	m_abilityExecuters(),
	m_playerID(playerID)
{

}

AbilityManager::~AbilityManager()
{
	// TODO if it needed
}

int AbilityManager::getCostOf(ABILITIES abilityType)
{
	int cost = INVALIDE_VALUE;
	if(m_abilityConfigs.keys().contains(abilityType))
	{
		cost = m_abilityConfigs[abilityType]->currCost;
	}
	else
	{
		qDebug() << "AbilityManager::getCostOf: Error! we have not this ability type: " << abilityType;
	}

	return cost;
}

void AbilityManager::registerAbilityType(ABILITIES type,
										 int minCost,
										 int maxCost,
										 int selfRecharge,
										 int maxRechargeWorks,
										 int costOfApply)
{
	if(!m_abilityConfigs.keys().contains(type))
	{
		AbilitySettings* settings = new AbilitySettings();
		settings->minCost = minCost;
		settings->maxCost = maxCost;
		settings->selfRecharge = selfRecharge;
		settings->fullRechargeWork = maxRechargeWorks;
		settings->currCost = minCost;
		settings->currentRechargeWorks = 0;
		settings->costOfApply = costOfApply;

		m_abilityConfigs[type] = settings;
	}
	else
	{
		qDebug() << "AbilityManager::registerAbilityType: Error! this ability already registred! type: " << type;
	}
}

int AbilityManager::abilityWasApplied(ABILITIES abilityType, Building* building)
{
	Q_UNUSED(abilityType)
	Q_UNUSED(building)

	qDebug() << "AbilityManager::abilityWasApplied: Error! this call should be reimplemented is subclasses!!!";
	return INVALIDE_VALUE;
}

void AbilityManager::init()
{
	qDebug() << "AbilityManager::init: Error! this call should be reimplemented is subclasses!!!";
}

int AbilityManager::increaseCostFor(ABILITIES type)
{
	if(m_abilityConfigs.keys().contains(type))
	{
		AbilitySettings* sett = m_abilityConfigs[type];
		int currWorks = sett->currentRechargeWorks + sett->costOfApply;

		if(currWorks > sett->fullRechargeWork)
		{
			currWorks = sett->fullRechargeWork;
		}


		sett->currentRechargeWorks = currWorks;
		int newCost = getCostFor(sett);

		sett->currCost = newCost;
		return newCost;
	}
	else
	{
		qDebug() << "AbilityManager::increaseCostFor: Error! we have not this ability type: " << type;
		return INVALIDE_VALUE;
	}
}


void AbilityManager::refreshAbilities()
{
	QMap<ABILITIES, AbilitySettings*>::iterator iter = m_abilityConfigs.begin();
	QMap<ABILITIES, AbilitySettings*>::iterator end = m_abilityConfigs.end();

	AbilityMenuController* abCntr = AbilityMenuController::getInstance();

	for(; iter != end; iter++)
	{
		AbilitySettings* sett = iter.value();
		sett->currentRechargeWorks -= sett->selfRecharge;

		if(sett->currentRechargeWorks < 0)
		{
			sett->currentRechargeWorks = 0;
		}

		sett->currCost = getCostFor(sett);

		if(m_playerID == MAIN_PLAYER_ID)
		{
			int subType = (int)iter.key();
			abCntr->setAbilityCost(ABILITY, subType, sett->currCost);
		}

	}
}

int AbilityManager::getCostFor(AbilitySettings *abilitySett)
{
	int newCost = ((abilitySett->maxCost - abilitySett->minCost) /
				   abilitySett->fullRechargeWork) * abilitySett->currentRechargeWorks + abilitySett->minCost;
	return newCost;
}
