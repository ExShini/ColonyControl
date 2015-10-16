#include "humanplayer.h"
#include "Enums/procsettings/humanprocessingsettings.h"
#include "Core/UnitController/unitcontroller.h"
#include "Core/objectcontroller.h"
#include "Human/humanbuildmanager.h"
#include "Human/humanabilitymanager.h"

HumanPlayer::HumanPlayer(int ID):
	Player(ID, Human)
{
	m_builManager = new HumanBuildManager();
	m_unitFactory = new HumanUnitFactory(m_ID);
	m_buildingFactory = new HumanBuildingFactory(m_ID);
	m_abilityManager = new HumanAbilityManager(m_ID);
}

HumanPlayer::~HumanPlayer()
{
	delete m_builManager;
	delete m_abilityManager;
	delete m_unitFactory;
	delete m_buildingFactory;
}

void HumanPlayer::init()
{
	Player::init();

	//register all resources limits
	setAllHumanLimits();

	//setup factory to UnitController
	UnitController::getInstance()->addUnitFactory(m_unitFactory, m_ID);
	ObjectController::getInstance()->addBuildingFactory(m_buildingFactory, m_ID);

	// init it here by the reason what HumanAbilityManager have dependency on UnitFactory
	m_abilityManager->init();
}

void HumanPlayer::setAllHumanLimits()
{

	/*
	POPULATION,
	SUPPLY,
	MINERALS,
	INFROSTRUCTURE,
	 */

	// HUMAN_SETTLERS
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 0, HUM_SETTLERS_SUP_LIM_0);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 1, HUM_SETTLERS_SUP_LIM_1);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 2, HUM_SETTLERS_SUP_LIM_2);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 3, HUM_SETTLERS_SUP_LIM_3);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 4, HUM_SETTLERS_SUP_LIM_4);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 5, HUM_SETTLERS_SUP_LIM_5);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 6, HUM_SETTLERS_SUP_LIM_6);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 7, HUM_SETTLERS_SUP_LIM_7);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 8, HUM_SETTLERS_SUP_LIM_8);
	setResLimit(t_HUMAN_SETTLERS, SUPPLY, 9, HUM_SETTLERS_SUP_LIM_9);

	setResLimit(t_HUMAN_SETTLERS, POPULATION, 0, HUM_SETTLERS_POP_LIM_0);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 1, HUM_SETTLERS_POP_LIM_1);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 2, HUM_SETTLERS_POP_LIM_2);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 3, HUM_SETTLERS_POP_LIM_3);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 4, HUM_SETTLERS_POP_LIM_4);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 5, HUM_SETTLERS_POP_LIM_5);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 6, HUM_SETTLERS_POP_LIM_6);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 7, HUM_SETTLERS_POP_LIM_7);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 8, HUM_SETTLERS_POP_LIM_8);
	setResLimit(t_HUMAN_SETTLERS, POPULATION, 9, HUM_SETTLERS_POP_LIM_9);

	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 0, HUM_SETTLERS_INF_LVL_0);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 1, HUM_SETTLERS_INF_LVL_1);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 2, HUM_SETTLERS_INF_LVL_2);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 3, HUM_SETTLERS_INF_LVL_3);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 4, HUM_SETTLERS_INF_LVL_4);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 5, HUM_SETTLERS_INF_LVL_5);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 6, HUM_SETTLERS_INF_LVL_6);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 7, HUM_SETTLERS_INF_LVL_7);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 8, HUM_SETTLERS_INF_LVL_8);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 9, HUM_SETTLERS_INF_LVL_9);
	setResLimit(t_HUMAN_SETTLERS, INFROSTRUCTURE, 10, HUM_SETTLERS_INF_LVL_9_max);


	// HUMAN_COLONY_CENTER
	setResLimit(t_HUMAN_COLONY_CENTER, SUPPLY, 0, HUM_COLONY_CENTER_SUP_LIM_0);
	setResLimit(t_HUMAN_COLONY_CENTER, SUPPLY, 1, HUM_COLONY_CENTER_SUP_LIM_1);
	setResLimit(t_HUMAN_COLONY_CENTER, SUPPLY, 2, HUM_COLONY_CENTER_SUP_LIM_2);
	setResLimit(t_HUMAN_COLONY_CENTER, SUPPLY, 3, HUM_COLONY_CENTER_SUP_LIM_3);

	setResLimit(t_HUMAN_COLONY_CENTER, POPULATION, 0, HUM_COLONY_CENTER_POP_LIM_0);
	setResLimit(t_HUMAN_COLONY_CENTER, POPULATION, 1, HUM_COLONY_CENTER_POP_LIM_1);
	setResLimit(t_HUMAN_COLONY_CENTER, POPULATION, 2, HUM_COLONY_CENTER_POP_LIM_2);
	setResLimit(t_HUMAN_COLONY_CENTER, POPULATION, 3, HUM_COLONY_CENTER_POP_LIM_3);

	setResLimit(t_HUMAN_COLONY_CENTER, INFROSTRUCTURE, 0, HUM_COLONY_CENTER_INF_LVL_0);
	setResLimit(t_HUMAN_COLONY_CENTER, INFROSTRUCTURE, 1, HUM_COLONY_CENTER_INF_LVL_1);
	setResLimit(t_HUMAN_COLONY_CENTER, INFROSTRUCTURE, 2, HUM_COLONY_CENTER_INF_LVL_2);
	setResLimit(t_HUMAN_COLONY_CENTER, INFROSTRUCTURE, 3, HUM_COLONY_CENTER_INF_LVL_3);
	setResLimit(t_HUMAN_COLONY_CENTER, INFROSTRUCTURE, 4, HUM_COLONY_CENTER_INF_LVL_3_max);

	setResLimit(t_HUMAN_COLONY_CENTER, SHIPS, 0, HUM_COLONY_CENTER_SHIPS_LIM_0);
	setResLimit(t_HUMAN_COLONY_CENTER, SHIPS, 1, HUM_COLONY_CENTER_SHIPS_LIM_1);
	setResLimit(t_HUMAN_COLONY_CENTER, SHIPS, 2, HUM_COLONY_CENTER_SHIPS_LIM_2);
	setResLimit(t_HUMAN_COLONY_CENTER, SHIPS, 3, HUM_COLONY_CENTER_SHIPS_LIM_3);


	// HUMAN_TRANSPORT_CENTER
	setResLimit(t_HUMAN_TRANSPORT_CENTER, SUPPLY, 0, HUM_TRANSPORT_CENTER_SUP_LIM_0);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, SUPPLY, 1, HUM_TRANSPORT_CENTER_SUP_LIM_1);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, SUPPLY, 2, HUM_TRANSPORT_CENTER_SUP_LIM_2);

	setResLimit(t_HUMAN_TRANSPORT_CENTER, POPULATION, 0, HUM_TRANSPORT_CENTER_POP_LIM_0);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, POPULATION, 1, HUM_TRANSPORT_CENTER_POP_LIM_1);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, POPULATION, 2, HUM_TRANSPORT_CENTER_POP_LIM_2);

	setResLimit(t_HUMAN_TRANSPORT_CENTER, INFROSTRUCTURE, 0, HUM_TRANSPORT_CENTER_INF_LVL_0);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, INFROSTRUCTURE, 1, HUM_TRANSPORT_CENTER_INF_LVL_1);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, INFROSTRUCTURE, 2, HUM_TRANSPORT_CENTER_INF_LVL_2);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, INFROSTRUCTURE, 3, HUM_TRANSPORT_CENTER_INF_LVL_2_max);

	setResLimit(t_HUMAN_TRANSPORT_CENTER, SHIPS, 0, HUM_TRANSPORT_CENTER_SHIPS_LIM_0);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, SHIPS, 1, HUM_TRANSPORT_CENTER_SHIPS_LIM_1);
	setResLimit(t_HUMAN_TRANSPORT_CENTER, SHIPS, 2, HUM_TRANSPORT_CENTER_SHIPS_LIM_2);
}


void HumanPlayer::setupHumanResPrototypes()
{
	// prepare common res prototype

	/******************************************/
	// m_populationProtoRes

	m_populationProtoRes = new Resourse();
	m_populationProtoRes->type = POPULATION;
	m_populationProtoRes->value = 0;
	// next value should be specified for each of building separetly
	m_populationProtoRes->maxValue = INVALIDE_VALUE;
	m_populationProtoRes->hardLimit = false;
	m_populationProtoRes->sizeOfGroup = GROUP_FROM_16;
	m_populationProtoRes->producebBy = POPULATION;
	m_populationProtoRes->producedForGroup = 1;

	// manufacturing for hard res
	m_populationProtoRes->complexityOfManufacturing = 1;
	m_populationProtoRes->currentProgress = 0;

	// material
	m_populationProtoRes->material = NO_RES;
	m_populationProtoRes->naturalMaterial = false;
	m_populationProtoRes->costOfMaterial = 0;

	//req resourse
	m_populationProtoRes->requaredRes = SUPPLY;
	m_populationProtoRes->consumeRes = 1;

	// export
	m_populationProtoRes->exportable = true;
	m_populationProtoRes->exportLimit = PERCENT_25;

	// import
	m_populationProtoRes->importable = true;
	m_populationProtoRes->importLimit = PERCENT_12a5;

	m_populationProtoRes->displayble = true;



	/******************************************/
	//m_supplyPropoRes

	m_supplyPropoRes = new Resourse();
	m_supplyPropoRes->type = SUPPLY;
	m_supplyPropoRes->value = 0;
	// next value should be specified for each of building separetly
	m_supplyPropoRes->maxValue = INVALIDE_VALUE;
	m_supplyPropoRes->hardLimit = false;
	m_supplyPropoRes->sizeOfGroup = GROUP_FROM_4;
	m_supplyPropoRes->producebBy = POPULATION;
	m_supplyPropoRes->producedForGroup = 19;

	// manufacturing for hard res
	m_supplyPropoRes->complexityOfManufacturing = 1;
	m_supplyPropoRes->currentProgress = 0;

	// material
	m_supplyPropoRes->material = FERTILITY;
	m_supplyPropoRes->naturalMaterial = true;
	m_supplyPropoRes->costOfMaterial = 0;

	//req resourse
	m_supplyPropoRes->requaredRes = NO_RES;
	m_supplyPropoRes->consumeRes = 0;

	// export
	m_supplyPropoRes->exportable = true;
	m_supplyPropoRes->exportLimit = PERCENT_25;

	// import
	m_supplyPropoRes->importable = false;
	m_supplyPropoRes->importLimit = PERCENT_25;

	m_supplyPropoRes->displayble = true;


	/******************************************/
	//m_transportShuttle

	m_transportShuttle = new Resourse();
	m_transportShuttle->type = SHIPS;
	m_transportShuttle->value = 0;
	// next value should be specified for each of building separetly
	m_transportShuttle->maxValue = INVALIDE_VALUE;
	m_transportShuttle->hardLimit = false;
	m_transportShuttle->sizeOfGroup = GROUP_FROM_1;
	m_transportShuttle->producebBy = POPULATION;
	m_transportShuttle->producedForGroup = 1;

	// manufacturing for hard res
	m_transportShuttle->complexityOfManufacturing = 2000;
	m_transportShuttle->currentProgress = 0;

	// material
	m_transportShuttle->material = NO_RES;
	m_transportShuttle->naturalMaterial = false;
	m_transportShuttle->costOfMaterial = 0;

	//req resourse
	m_transportShuttle->requaredRes = NO_RES;
	m_transportShuttle->consumeRes = 0;

	// export
	m_transportShuttle->exportable = true;
	m_transportShuttle->exportLimit = PERCENT_25;

	// import
	m_transportShuttle->importable = false;
	m_transportShuttle->importLimit = PERCENT_25;

	m_transportShuttle->displayble = true;
}
