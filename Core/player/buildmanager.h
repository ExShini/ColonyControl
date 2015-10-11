#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include <qmap.h>
#include "Enums/objects.h"

class BuildManager
{
public:
	explicit BuildManager();
	virtual ~BuildManager();
	virtual int getCostOf(OBJECT_TYPE objType);
	virtual int objectWasBuilded(OBJECT_TYPE objType);
	virtual int objectWasDestroed(OBJECT_TYPE objType);

protected:
	void registerBuildingType(OBJECT_TYPE type, int defaultConst);

	QMap<OBJECT_TYPE, int> m_buildingCost;
	QMap<OBJECT_TYPE, int> m_buildingDefCost;

};

#endif // BUILDMANAGER_H
