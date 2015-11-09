#include "humanplayer.h"
#include "Enums/procsettings/humanprocessingsettings.h"
#include "Core/UnitController/unitcontroller.h"
#include "Core/objectcontroller.h"
#include "humanbuildmanager.h"
#include "humanabilitymanager.h"

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

	//prepare common res prototypes
	prepareHumanResPrototypes();

	//setup res prototupe and specific settings
	setupHumanResPrototypes();

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
	// HUMAN_COLONY_CENTER
	for(int level = 0; level <= HUMAN_MAX_COLONY_CENTER_LEVEL; level++)
	{
		setResToPrototype(t_HUMAN_COLONY_CENTER, m_populationProtoRes, level);
		setResToPrototype(t_HUMAN_COLONY_CENTER, m_supplyProtoRes, level);
		setResToPrototype(t_HUMAN_COLONY_CENTER, m_transportShuttle, level);
		setResToPrototype(t_HUMAN_COLONY_CENTER, m_infrastructure[level], level);
	}
	setResToPrototype(t_HUMAN_COLONY_CENTER,
					  m_infrastructure[HUMAN_MAX_COLONY_CENTER_LEVEL + 1],
					  HUMAN_MAX_COLONY_CENTER_LEVEL + 1);
	// setup default value
	setDefValue(t_HUMAN_COLONY_CENTER, SHIPS, 1);
	setDefValue(t_HUMAN_COLONY_CENTER, POPULATION, 800);
	setDefValue(t_HUMAN_COLONY_CENTER, SUPPLY, 800);


	// HUMAN_SETTLERS
	for(int level = 0; level <= HUMAN_MAX_SETTLEMENT_LEVEL; level++)
	{
		setResToPrototype(t_HUMAN_SETTLERS, m_populationProtoRes, level);
		setResToPrototype(t_HUMAN_SETTLERS, m_supplyProtoRes, level);
		setResToPrototype(t_HUMAN_SETTLERS, m_infrastructure[level], level);
	}
	setResToPrototype(t_HUMAN_SETTLERS,
					  m_infrastructure[HUMAN_MAX_SETTLEMENT_LEVEL + 1],
					  HUMAN_MAX_SETTLEMENT_LEVEL + 1);


	//  HUMAN_TRANSPORT_CENTER
	for(int level = 0; level <= HUMAN_MAX_TRANSPORT_CENTER_LEVEL; level++)
	{
		setResToPrototype(t_HUMAN_TRANSPORT_CENTER, m_populationProtoRes, level);
		setResToPrototype(t_HUMAN_TRANSPORT_CENTER, m_supplyProtoRes, level);
		setResToPrototype(t_HUMAN_TRANSPORT_CENTER, m_infrastructure[level], level);
		setResToPrototype(t_HUMAN_TRANSPORT_CENTER, m_transportShuttle, level);
	}
	setResToPrototype(t_HUMAN_TRANSPORT_CENTER,
					  m_infrastructure[HUMAN_MAX_TRANSPORT_CENTER_LEVEL + 1],
					  HUMAN_MAX_TRANSPORT_CENTER_LEVEL + 1);

}

void HumanPlayer::prepareHumanResPrototypes()
{
	// prepare common res prototype

	/******************************************/
	// m_populationProtoRes
	{
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
		m_populationProtoRes->hardRequirement = true;

		// export
		m_populationProtoRes->exportable = true;
		m_populationProtoRes->exportLimit = PERCENT_25;

		// import
		m_populationProtoRes->importable = true;
		m_populationProtoRes->importLimit = PERCENT_12a5;

		m_populationProtoRes->displayble = true;
	}

	/******************************************/
	//m_supplyProtoRes
	{
		m_supplyProtoRes = new Resourse();
		m_supplyProtoRes->type = SUPPLY;
		m_supplyProtoRes->value = 0;
		// next value should be specified for each of building separetly
		m_supplyProtoRes->maxValue = INVALIDE_VALUE;
		m_supplyProtoRes->hardLimit = true;
		m_supplyProtoRes->sizeOfGroup = GROUP_FROM_4;
		m_supplyProtoRes->producebBy = POPULATION;
		m_supplyProtoRes->producedForGroup = 19;

		// manufacturing for hard res
		m_supplyProtoRes->complexityOfManufacturing = 1;
		m_supplyProtoRes->currentProgress = 0;

		// material
		m_supplyProtoRes->material = FERTILITY;
		m_supplyProtoRes->naturalMaterial = true;
		m_supplyProtoRes->costOfMaterial = 0;

		//req resourse
		m_supplyProtoRes->requaredRes = NO_RES;
		m_supplyProtoRes->consumeRes = 0;
		m_supplyProtoRes->hardRequirement = false;

		// export
		m_supplyProtoRes->exportable = true;
		m_supplyProtoRes->exportLimit = PERCENT_25;

		// import
		m_supplyProtoRes->importable = false;
		m_supplyProtoRes->importLimit = PERCENT_25;

		m_supplyProtoRes->displayble = true;
	}

	/******************************************/
	//m_transportShuttle
	{
		m_transportShuttle = new Resourse();
		m_transportShuttle->type = SHIPS;
		m_transportShuttle->value = 0;
		// next value should be specified for each of building separetly
		m_transportShuttle->maxValue = INVALIDE_VALUE;
		m_transportShuttle->hardLimit = true;
		m_transportShuttle->sizeOfGroup = GROUP_FROM_1;
		m_transportShuttle->producebBy = POPULATION;
		m_transportShuttle->producedForGroup = 1;

		// manufacturing for hard res
		m_transportShuttle->complexityOfManufacturing = 1400;
		m_transportShuttle->currentProgress = 0;

		// material
		m_transportShuttle->material = NO_RES;
		m_transportShuttle->naturalMaterial = false;
		m_transportShuttle->costOfMaterial = 0;

		//req resourse
		m_transportShuttle->requaredRes = NO_RES;
		m_transportShuttle->consumeRes = 0;
		m_transportShuttle->hardRequirement = false;

		// export
		m_transportShuttle->exportable = true;
		m_transportShuttle->exportLimit = INVALIDE_VALUE;

		// import
		m_transportShuttle->importable = false;
		m_transportShuttle->importLimit = INVALIDE_VALUE;

		m_transportShuttle->displayble = true;
	}

	/******************************************/
	//m_infrastructure
	{
		Resourse* infrastr = new Resourse();
		infrastr = new Resourse();
		infrastr->type = INFROSTRUCTURE;
		infrastr->value = 0;
		// next value should be specified for each of building separetly
		infrastr->maxValue = INVALIDE_VALUE;
		infrastr->hardLimit = true;
		infrastr->sizeOfGroup = GROUP_FROM_8;
		infrastr->producebBy = POPULATION;
		infrastr->producedForGroup = 1;

		// manufacturing for hard res
		infrastr->complexityOfManufacturing = 1;
		infrastr->currentProgress = 0;

		// material
		infrastr->material = NO_RES;
		infrastr->naturalMaterial = false;
		infrastr->costOfMaterial = 0;

		//req resourse
		infrastr->requaredRes = NO_RES;
		infrastr->consumeRes = 0;
		infrastr->hardRequirement = false;

		// export
		infrastr->exportable = false;
		infrastr->exportLimit = INVALIDE_VALUE;

		// import
		infrastr->importable = false;
		infrastr->importLimit = INVALIDE_VALUE;

		infrastr->displayble = true;

		// 0 lvl
		m_infrastructure[0] = infrastr;

		// 1 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 2;
		m_infrastructure[1] = infrastr;

		// 2 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 4;
		m_infrastructure[2] = infrastr;

		// 3 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 8;
		m_infrastructure[3] = infrastr;

		// 4 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 16;
		m_infrastructure[4] = infrastr;

		// 5 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 32;
		m_infrastructure[5] = infrastr;

		// 6 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 64;
		m_infrastructure[6] = infrastr;

		// 7 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 128;
		m_infrastructure[7] = infrastr;

		// 8 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 256;
		m_infrastructure[8] = infrastr;

		// 9 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 512;
		m_infrastructure[9] = infrastr;

		// 10 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 1024;
		m_infrastructure[9] = infrastr;

		// 11 lvl
		infrastr = new Resourse(infrastr);
		infrastr->complexityOfManufacturing = 2048;
		m_infrastructure[10] = infrastr;
	}
}
