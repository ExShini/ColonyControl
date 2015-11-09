#ifndef AROIBUILDMANAGER_H
#define AROIBUILDMANAGER_H
#include "../buildmanager.h"

class AroiBuildManager: public BuildManager
{
public:
	AroiBuildManager();
	virtual ~AroiBuildManager();
	virtual int getCostOf(OBJECT_TYPE objType);
};


#endif // AROIBUILDMANAGER_H
