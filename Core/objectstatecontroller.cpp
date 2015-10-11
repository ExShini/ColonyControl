#include "objectstatecontroller.h"
#include "qdebug.h"

ObjectStateController* ObjectStateController::s_instance = nullptr;

ObjectStateController::ObjectStateController()
{
	resetConditions();
}

ObjectStateController::~ObjectStateController()
{

}

ObjectStateController* ObjectStateController::getInstance()
{
	if(s_instance == nullptr)
	{
		s_instance = new ObjectStateController();
	}

	return s_instance;
}

void ObjectStateController::resetConditions()
{
	for(int i = 0; i < MAX_ACTIVE_GAME_OBJECT; i++)
	{
		m_buildStatus[i] = NO_CONDITION;
		m_unitStatus[i] = NO_CONDITION;
	}
}

void ObjectStateController::addBuilding(int id)
{
	if(id < MAX_ACTIVE_GAME_OBJECT && id >= 0)
	{
		m_buildStatus[id] = NORMAL_EMPTY_CONDITION;
	}
	else
	{
		qDebug() << "ObjectStateController::addBuilding: Error! incorrect id: " << id;
	}
}

bool ObjectStateController::chackBuildingCondition(int objectID, int condition)
{
	bool result = false;

	if(objectID < MAX_ACTIVE_GAME_OBJECT && objectID >= 0)
	{
		int status = m_buildStatus[objectID];
		result = CHECK_CONDITION(condition,status) != NO_CONDITION;
	}
	else
	{
		qDebug() << "ObjectStateController::chackBuildingCondition: Error! incorrect objectID: " << objectID;
	}

	return result;
}

void ObjectStateController::setBuildingCondition(int objectID, int condition)
{
	if(objectID < MAX_ACTIVE_GAME_OBJECT && objectID >= 0)
	{
		int currState = m_buildStatus[objectID];
		m_buildStatus[objectID] = ADD_CONDITION(condition, currState);
	}
	else
	{
		qDebug() << "ObjectStateController::setBuildingCondition: Error! incorrect objectID: " << objectID;
	}
}



void ObjectStateController::addUnit(int id)
{
	if(id < MAX_ACTIVE_GAME_OBJECT && id >= 0)
	{
		m_unitStatus[id] = NORMAL_EMPTY_CONDITION;
	}
	else
	{
		qDebug() << "ObjectStateController::addBuilding: Error! incorrect id: " << id;
	}
}

bool ObjectStateController::chackUnitCondition(int objectID, int condition)
{
	bool result = false;

	if(objectID < MAX_ACTIVE_GAME_OBJECT && objectID >= 0)
	{
		int status = m_unitStatus[objectID];
		result = CHECK_CONDITION(condition,status) != NO_CONDITION;
	}
	else
	{
		qDebug() << "ObjectStateController::chackUnitCondition: Error! incorrect objectID: " << objectID;
	}

	return result;
}

void ObjectStateController::setUnitCondition(int objectID, int condition)
{
	if(objectID < MAX_ACTIVE_GAME_OBJECT && objectID >= 0)
	{
		int currState = m_unitStatus[objectID];
		m_unitStatus[objectID] = ADD_CONDITION(condition, currState);
	}
	else
	{
		qDebug() << "ObjectStateController::setBuildingCondition: Error! incorrect objectID: " << objectID;
	}
}
