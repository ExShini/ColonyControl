#ifndef HUMANBUILDMANAGER_H
#define HUMANBUILDMANAGER_H
#include "../buildmanager.h"

class HumanBuildManager: public BuildManager
{
public:
	HumanBuildManager();
	virtual ~HumanBuildManager();
	virtual int getCostOf(OBJECT_TYPE objType);
};

#endif // HUMANBUILDMANAGER_H
