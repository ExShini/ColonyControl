#include "aroiplayer.h"

#include "Enums/procsettings/aroiprocessingsettings.h"
#include "Core/UnitController/unitcontroller.h"
#include "Core/objectcontroller.h"
#include "aroibuildmanager.h"
#include "aroiabilitymanager.h"



// ResPrototypeStotage for all AROI buildings
static ResPrototypeStotage s_aroiResourses[] =
{
	// t_AROI_HIVE
	// BUILDING TYPE   lvl		 RES TYPE	   VALUE(N.S)		MAX VALUE		  HARD LIM		SIZE OF GROUP		PRODECED BY		GROUP PROD.	  COMPL.	 PROGRESS(N.S)	   MATERIAL	   MAT. COST	NATURAL	    REQUARED	 CONSUME   HARD REQ.   IMPORT	IMP. LIMIT	   EXPORT	EXP. LIMIT	   DISPLAY
	{	t_AROI_HIVE,	0,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_0,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	1,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_1,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	2,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_2,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	3,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_3,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	4,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_4,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	5,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_5,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	6,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_6,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	7,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_7,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	8,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_8,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	9,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_9,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},
	{	t_AROI_HIVE,	10,		{POPULATION,	NOT_SET,	AROI_HIVE_POP_LIM_10,	false,		GROUP_FROM_16,		POPULATION,			2,			1,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	SUPPLY,			1,		true,		true,	PERCENT_25,		true,	PERCENT_25,		true}},

	// BUILDING TYPE   lvl		 RES TYPE	   VALUE(N.S)		MAX VALUE		  HARD LIM		SIZE OF GROUP		PRODECED BY		GROUP PROD.	  COMPL.	 PROGRESS(N.S)	   MATERIAL	   MAT. COST	NATURAL	    REQUARED	 CONSUME   HARD REQ.   IMPORT	IMP. LIMIT	   EXPORT	EXP. LIMIT	   DISPLAY
	{	t_AROI_HIVE,	0,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_0,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	1,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_1,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	2,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_2,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	3,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_3,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	4,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_4,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	5,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_5,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	6,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_6,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	7,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_7,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	8,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_8,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	9,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_9,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	10,		{SUPPLY,		NOT_SET,	AROI_HIVE_SUP_LIM_10,	false,		GROUP_FROM_4,		POPULATION,			21,			1,			NOT_SET,		FERTILITY,	MAT_COST_1,	true,		NO_RES,		 NOT_SET,	NOT_SET,	true,	PERCENT_25,		false,	NOT_SET,		true}},

	// BUILDING TYPE   lvl		 RES TYPE	   VALUE(N.S)		MAX VALUE		  HARD LIM		SIZE OF GROUP		PRODECED BY		GROUP PROD.	  COMPL.	 PROGRESS(N.S)	   MATERIAL	   MAT. COST	NATURAL	    REQUARED	 CONSUME   HARD REQ.   IMPORT	IMP. LIMIT	   EXPORT	EXP. LIMIT	   DISPLAY
	{	t_AROI_HIVE,	0,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_0,	 true,		GROUP_FROM_8,		POPULATION,			1,			2,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	1,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_1,	 true,		GROUP_FROM_8,		POPULATION,			1,			4,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	2,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_2,	 true,		GROUP_FROM_8,		POPULATION,			1,			8,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	3,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_3,	 true,		GROUP_FROM_8,		POPULATION,			1,			16,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	4,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_4,	 true,		GROUP_FROM_8,		POPULATION,			1,			32,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	5,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_5,	 true,		GROUP_FROM_8,		POPULATION,			1,			64,			NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	6,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_6,	 true,		GROUP_FROM_8,		POPULATION,			1,			128,		NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	7,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_7,	 true,		GROUP_FROM_8,		POPULATION,			1,			256,		NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	8,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_8,	 true,		GROUP_FROM_8,		POPULATION,			1,			512,		NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	9,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_9,	 true,		GROUP_FROM_8,		POPULATION,			1,			1024,		NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	10,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_10,	 true,		GROUP_FROM_8,		POPULATION,			1,			2048,		NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},
	{	t_AROI_HIVE,	11,		{INFROSTRUCTURE,NOT_SET,	AROI_HIVE_INF_LVL_10_max,true,		GROUP_FROM_8,		POPULATION,			1,			2048,		NOT_SET,		NO_RES,		NOT_SET,	NOT_SET,	NO_RES,		 NOT_SET,	NOT_SET,	false,	NOT_SET,		false,	NOT_SET,		true}},

};

static DefResSetting s_aroiDefResValue[]
{
	//	BUILDING TYPE		RES TYPE			DEF VALUE
	{	t_AROI_HIVE,		POPULATION,			NOT_SET					},
	{	t_AROI_HIVE,		SUPPLY,				NOT_SET					},
	{	t_AROI_HIVE,		INFROSTRUCTURE,		AROI_HIVE_INF_LVL_1 + 1	}
};

AroiPlayer::AroiPlayer(int ID):
	Player(ID, Aroi)
{
	m_abilityManager = new AroiAbilityManager(m_ID);
	m_builManager = new AroiBuildManager();
	m_unitFactory = new AroiUnitFactory(m_ID);
	m_buildingFactory = new AroiBuildingFactory(m_ID);
}

AroiPlayer::~AroiPlayer()
{
	if(m_builManager != nullptr)
	{
		delete m_builManager;
	}

	if(m_abilityManager != nullptr)
	{
		delete m_abilityManager;
	}

	if(m_unitFactory != nullptr)
	{
		delete m_unitFactory;
	}

	if(m_buildingFactory != nullptr)
	{
		delete m_buildingFactory;
	}
}

void AroiPlayer::init()
{
	Player::init();

	setupAroiResPrototypes();
	setAroiResDefValue();

	//setup factory to UnitController
	UnitController::getInstance()->addUnitFactory(m_unitFactory, m_ID);
	ObjectController::getInstance()->addBuildingFactory(m_buildingFactory, m_ID);

	// init it here by the reason what HumanAbilityManager have dependency on UnitFactory
	m_abilityManager->init();
}

void AroiPlayer::setupAroiResPrototypes()
{
	int prototypeStorageSize = sizeof(s_aroiResourses) / sizeof(ResPrototypeStotage);

	for(int i = 0; i < prototypeStorageSize; i++)
	{
		ResPrototypeStotage& proto = s_aroiResourses[i];

		OBJECT_TYPE buildType = proto.type;
		int lvl = proto.level;
		Resourse* res = &(proto.resorse);

		setResToPrototype(buildType, res, lvl);
	}
}


void AroiPlayer::setAroiResDefValue()
{
	int defValStorageSize = sizeof(s_aroiDefResValue) / sizeof(DefResSetting);

	for(int i = 0; i < defValStorageSize; i++)
	{
		DefResSetting& proto = s_aroiDefResValue[i];

		OBJECT_TYPE buildType = proto.type;
		RESOURSES resType = proto.resType;
		int value = proto.defaulValue;

		setDefValue(buildType, resType, value);
	}
}
