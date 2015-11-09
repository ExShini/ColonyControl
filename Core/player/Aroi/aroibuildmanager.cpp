#include "aroibuildmanager.h"

AroiBuildManager::AroiBuildManager():
	BuildManager()
{
}

AroiBuildManager::~AroiBuildManager()
{

}


int AroiBuildManager::getCostOf(OBJECT_TYPE objType)
{
	if(objType == t_AROI_HIVE)
		return 0;

	return BuildManager::getCostOf(objType);
}
