#include "humanbuildmanager.h"

HumanBuildManager::HumanBuildManager():
	BuildManager()
{
	registerBuildingType(t_HUMAN_TRANSPORT_CENTER, 3000);
}

HumanBuildManager::~HumanBuildManager()
{

}
