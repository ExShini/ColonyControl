#include "objectstatecontroller.h"
#include "qdebug.h"

ObjectStateController* ObjectStateController::s_instance = nullptr;

ObjectStateController::ObjectStateController():
	m_idCnt(0)
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
		m_objectsStatus[i] = NO_CONDITION;
	}

	m_idCnt = 0;
}

void ObjectStateController::addGObject(int id)
{
	if(id < MAX_ACTIVE_GAME_OBJECT && id >= 0)
	{
		m_objectsStatus[id] = NORMAL_EMPTY_CONDITION;
	}
	else
	{
		qDebug() << "ObjectStateController::addGObject: Error! incorrect id: " << id;
	}
}

int ObjectStateController::getNewGObjectID()
{
	int currID = m_idCnt;
	m_idCnt++;
	return currID;
}

bool ObjectStateController::chackGObjectCondition(int objectID, int condition)
{
	bool result = false;

	if(objectID < MAX_ACTIVE_GAME_OBJECT && objectID >= 0)
	{
		int status = m_objectsStatus[objectID];
		result = CHECK_CONDITION(condition,status) != NO_CONDITION;
	}
	else
	{
		qDebug() << "ObjectStateController::chackGObjectCondition: Error! incorrect objectID: " << objectID;
	}

	return result;
}

void ObjectStateController::setGObjectCondition(int objectID, int condition)
{
	if(objectID < MAX_ACTIVE_GAME_OBJECT && objectID >= 0)
	{
		int currState = m_objectsStatus[objectID];
		m_objectsStatus[objectID] = ADD_CONDITION(condition, currState);
	}
	else
	{
		qDebug() << "ObjectStateController::setGObjectCondition: Error! incorrect objectID: " << objectID;
	}
}
