#include "aroiplayer.h"

#include "Enums/procsettings/aroiprocessingsettings.h"
#include "Core/UnitController/unitcontroller.h"
#include "Core/objectcontroller.h"
#include "aroibuildmanager.h"
#include "aroiabilitymanager.h"

AroiPlayer::AroiPlayer(int ID):
	Player(ID, Aroi)
{
	m_abilityManager = new AbilityManager(m_ID);
	m_builManager = new AroiBuildManager();
	m_unitFactory = new AroiUnitFactory(m_ID);
	m_buildingFactory = new AroiBuildingFactory(m_ID);
}

AroiPlayer::~AroiPlayer()
{
	delete m_unitFactory;
	//	delete m_buildingFactory;
}

void AroiPlayer::init()
{
	Player::init();

	//prepare common res prototypes
	prepareAroiResPrototypes();

	//setup res prototupe and specific settings
	setupAroiResPrototypes();

	//register all resources limits
	setAllAroiLimits();

	//setup factory to UnitController
	//	UnitController::getInstance()->addUnitFactory(m_unitFactory, m_ID);
	//	ObjectController::getInstance()->addBuildingFactory(m_buildingFactory, m_ID);

	// init it here by the reason what HumanAbilityManager have dependency on UnitFactory
	m_abilityManager->init();
}

void AroiPlayer::setAllAroiLimits()
{

	/*
	POPULATION,
	SUPPLY,
	MINERALS,
	INFROSTRUCTURE,
	 */

	// HUMAN_SETTLERS
	//	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 0, HUM_SETTLERS_SUP_LIM_0);

	//	setResLimit(t_HUMAN_SETTLERS, POPULATION, 0, HUM_SETTLERS_POP_LIM_0);

	//	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 0, HUM_SETTLERS_INF_LVL_0);

}


void AroiPlayer::setupAroiResPrototypes()
{
	// TODO
}

void AroiPlayer::prepareAroiResPrototypes()
{
	// TODO
}
