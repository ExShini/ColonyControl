#include "humanbuildmanager.h"

HumanBuildManager::HumanBuildManager():
	BuildManager()
{
	registerBuildingType(t_HUMAN_TRANSPORT_CENTER, 3000);
}

HumanBuildManager::~HumanBuildManager()
{

}


int HumanBuildManager::getCostOf(OBJECT_TYPE objType)
{
	if(objType == t_HUMAN_SETTLERS)
		return 0;

	return BuildManager::getCostOf(objType);
}
