#include "buildmanager.h"
#include "qdebug.h"

BuildManager::BuildManager()
{

}

BuildManager::~BuildManager()
{

}

int BuildManager::getCostOf(OBJECT_TYPE objType)
{
	if(m_buildingCost.keys().contains(objType))
	{
		return m_buildingCost[objType];
	}
	else
	{
		qDebug() << "BuildManager::getCostOf: Error! unregistred type: " << objType;
		return INVALIDE_VALUE;
	}
}

void BuildManager::registerBuildingType(OBJECT_TYPE type, int defaultConst)
{
	if(!m_buildingCost.keys().contains(type))
	{
		m_buildingCost[type] = defaultConst;
		m_buildingDefCost[type] = defaultConst;
	}
	else
	{
		qDebug() << "BuildManager::registerBuildingType: Error! Already registred type: " << type;
	}
}

int BuildManager::objectWasBuilded(OBJECT_TYPE objType)
{
	// TODO
	int cost = getCostOf(objType);
	if(cost != INVALIDE_VALUE)
	{
		cost = cost * 3;
		m_buildingCost[objType] = cost;
	}

	return cost;
}


int BuildManager::objectWasDestroed(OBJECT_TYPE objType)
{
	// TODO
	int cost = getCostOf(objType);
	if(cost != INVALIDE_VALUE)
	{
		cost = cost / 3;
		int defCost = m_buildingDefCost[objType];

		if(cost < defCost)
		{
			cost = defCost;
		}

		m_buildingCost[objType] = cost;
	}

	return cost;
}
