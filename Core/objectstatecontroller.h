#ifndef OBJECTSTATECONTROLLER_H
#define OBJECTSTATECONTROLLER_H
#include "Enums/objstatus.h"


class ObjectStateController
{
public:
	static ObjectStateController* getInstance();
	virtual ~ObjectStateController();

	void resetConditions();

	void addBuilding(int id);
	void addUnit(int id);

	void setBuildingCondition(int objectID, int condition);
	void setUnitCondition(int objectID, int condition);

	bool chackBuildingCondition(int objectID, int condition);
	bool chackUnitCondition(int objectID, int condition);

protected:
	ObjectStateController();
	static ObjectStateController* s_instance;

	int m_buildStatus[MAX_ACTIVE_GAME_OBJECT];
	int m_unitStatus[MAX_ACTIVE_GAME_OBJECT];
};

#endif // OBJECTSTATECONTROLLER_H
