#ifndef OBJECTSTATECONTROLLER_H
#define OBJECTSTATECONTROLLER_H
#include "Enums/objstatus.h"


class ObjectStateController
{
public:
	static ObjectStateController* getInstance();
	virtual ~ObjectStateController();

	void resetConditions();

	int getNewGObjectID();
	void addGObject(int id);
	void setGObjectCondition(int objectID, int condition);
	bool chackGObjectCondition(int objectID, int condition);

protected:
	ObjectStateController();
	static ObjectStateController* s_instance;

	int m_objectsStatus[MAX_ACTIVE_GAME_OBJECT];
	int m_idCnt;
};

#endif // OBJECTSTATECONTROLLER_H
