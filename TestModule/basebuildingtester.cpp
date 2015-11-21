#include "basebuildingtester.h"
#include "Core/playercontroller.h"
#include "Core/gobjwrapper.h"
#include "qdebug.h"


/******************************
 * TestBuilding
 * Test object for validation of new version resource processing
 *
 *****************************/
TestBuilding::TestBuilding():
	Building(new GObjWrapper(), new Sector(), 0, 0)
{
}

void TestBuilding::execResProcess()
{
	processResource();
}

void TestBuilding::setup1Env()
{
	// supply
	Resourse* supply = new Resourse();
	// values
	supply->type = SUPPLY;
	supply->value = 0;
	supply->maxValue = 1000;

	supply->hardLimit = true;
	supply->sizeOfGroup = GROUP_FROM_4;
	supply->producebBy = POPULATION;
	supply->producedForGroup = 19;

	// manufacturing for hard res
	supply->complexityOfManufacturing = 1;
	supply->currentProgress = 0;

	// material
	supply->material = FERTILITY;
	supply->naturalMaterial = true;
	supply->costOfMaterial = 1;

	//req resourse
	supply->requaredRes = NO_RES;
	supply->consumeRes = 0;


	// export
	supply->exportable = false;
	supply->exportLimit = 0;

	// import
	supply->importable = true;
	supply->importLimit = PERCENT_25;

	supply->displayble = true;
	m_resources[supply->type] = supply;


	/****************************/
	// population

	Resourse* population = new Resourse();
	// values
	population->type = POPULATION;
	population->value = 160;
	population->maxValue = 1000;

	population->hardLimit = true;
	population->sizeOfGroup = GROUP_FROM_16;
	population->producebBy = POPULATION;
	population->producedForGroup = 0;

	// manufacturing for hard res
	population->complexityOfManufacturing = 1;
	population->currentProgress = 0;

	// material
	population->material = NO_RES;
	population->naturalMaterial = false;
	population->costOfMaterial = 0;

	//req resourse
	population->requaredRes = NO_RES;
	population->consumeRes = 0;

	// export
	population->exportable = false;
	population->exportLimit = 0;

	// import
	population->importable = false;
	population->importLimit = PERCENT_25;

	population->displayble = true;
	m_resources[population->type] = population;

	// sector settings
	m_sector->setFertility(1000);
}

void TestBuilding::setup2Env()
{
	// supply
	Resourse* supply = new Resourse();
	// values
	supply->type = SUPPLY;
	supply->value = 1000;
	supply->maxValue = 1000;

	supply->hardLimit = false;
	supply->sizeOfGroup = GROUP_FROM_4;
	supply->producebBy = POPULATION;
	supply->producedForGroup = 10;

	// manufacturing for hard res
	supply->complexityOfManufacturing = 1;
	supply->currentProgress = 0;

	// material
	supply->material = FERTILITY;
	supply->naturalMaterial = true;
	supply->costOfMaterial = 1;

	//req resourse
	supply->requaredRes = NO_RES;
	supply->consumeRes = 0;


	// export
	supply->exportable = false;
	supply->exportLimit = 0;

	// import
	supply->importable = true;
	supply->importLimit = PERCENT_25;

	supply->displayble = true;
	m_resources[supply->type] = supply;


	/****************************/
	// population

	Resourse* population = new Resourse();
	// values
	population->type = POPULATION;
	population->value = 160;
	population->maxValue = 1000;

	population->hardLimit = true;
	population->sizeOfGroup = GROUP_FROM_16;
	population->producebBy = POPULATION;
	population->producedForGroup = 0;

	// manufacturing for hard res
	population->complexityOfManufacturing = 1;
	population->currentProgress = 0;

	// material
	population->material = NO_RES;
	population->naturalMaterial = false;
	population->costOfMaterial = 0;

	//req resourse
	population->requaredRes = NO_RES;
	population->consumeRes = 0;

	// export
	population->exportable = false;
	population->exportLimit = 0;

	// import
	population->importable = false;
	population->importLimit = PERCENT_25;

	population->displayble = true;
	m_resources[population->type] = population;

	// sector settings
	m_sector->setFertility(1000);
}

void TestBuilding::setup3Env()
{
	// supply
	Resourse* supply = new Resourse();
	// values
	supply->type = SUPPLY;
	supply->value = 1000;
	supply->maxValue = 1000;

	supply->hardLimit = false;
	supply->sizeOfGroup = GROUP_FROM_4;
	supply->producebBy = POPULATION;
	supply->producedForGroup = 10;

	// manufacturing for hard res
	supply->complexityOfManufacturing = 1;
	supply->currentProgress = 0;

	// material
	supply->material = FERTILITY;
	supply->naturalMaterial = true;
	supply->costOfMaterial = 1;

	//req resourse
	supply->requaredRes = NO_RES;
	supply->consumeRes = 0;


	// export
	supply->exportable = true;
	supply->exportLimit = PERCENT_25;

	// import
	supply->importable = true;
	supply->importLimit = PERCENT_25;

	supply->displayble = true;
	m_resources[supply->type] = supply;


	/****************************/
	// population

	Resourse* population = new Resourse();
	// values
	population->type = POPULATION;
	population->value = 160;
	population->maxValue = 1000;

	population->hardLimit = true;
	population->sizeOfGroup = GROUP_FROM_16;
	population->producebBy = POPULATION;
	population->producedForGroup = 0;

	// manufacturing for hard res
	population->complexityOfManufacturing = 1;
	population->currentProgress = 0;

	// material
	population->material = NO_RES;
	population->naturalMaterial = false;
	population->costOfMaterial = 0;

	//req resourse
	population->requaredRes = NO_RES;
	population->consumeRes = 0;

	// export
	population->exportable = false;
	population->exportLimit = 0;

	// import
	population->importable = false;
	population->importLimit = PERCENT_25;

	population->displayble = true;
	m_resources[population->type] = population;

	// sector settings
	m_sector->setFertility(1000);
}

void TestBuilding::setup4Env()
{
	// supply
	Resourse* supply = new Resourse();
	// values
	supply->type = SUPPLY;
	supply->value = 0;
	supply->maxValue = 1000;

	supply->hardLimit = false;
	supply->sizeOfGroup = GROUP_FROM_4;
	supply->producebBy = POPULATION;
	supply->producedForGroup = 10;

	// manufacturing for hard res
	supply->complexityOfManufacturing = 1;
	supply->currentProgress = 0;

	// material
	supply->material = FERTILITY;
	supply->naturalMaterial = true;
	supply->costOfMaterial = 1;

	//req resourse
	supply->requaredRes = NO_RES;
	supply->consumeRes = 0;


	// export
	supply->exportable = true;
	supply->exportLimit = PERCENT_25;

	// import
	supply->importable = true;
	supply->importLimit = PERCENT_25;

	supply->displayble = true;
	m_resources[supply->type] = supply;


	/****************************/
	// population

	Resourse* population = new Resourse();
	// values
	population->type = POPULATION;
	population->value = 160;
	population->maxValue = 1000;

	population->hardLimit = true;
	population->sizeOfGroup = GROUP_FROM_16;
	population->producebBy = POPULATION;
	population->producedForGroup = 0;

	// manufacturing for hard res
	population->complexityOfManufacturing = 1;
	population->currentProgress = 0;

	// material
	population->material = NO_RES;
	population->naturalMaterial = false;
	population->costOfMaterial = 0;

	//req resourse
	population->requaredRes = NO_RES;
	population->consumeRes = 0;

	// export
	population->exportable = false;
	population->exportLimit = 0;

	// import
	population->importable = false;
	population->importLimit = PERCENT_25;

	population->displayble = true;
	m_resources[population->type] = population;

	// sector settings
	m_sector->setFertility(1000);
}

void TestBuilding::setup5Env()
{
	// supply
	Resourse* supply = new Resourse();
	// values
	supply->type = SUPPLY;
	supply->value = 50;
	supply->maxValue = 1000;

	supply->hardLimit = false;
	supply->sizeOfGroup = GROUP_FROM_4;
	supply->producebBy = NO_RES;
	supply->producedForGroup = 0;

	// manufacturing for hard res
	supply->complexityOfManufacturing = 1;
	supply->currentProgress = 0;

	// material
	supply->material = FERTILITY;
	supply->naturalMaterial = true;
	supply->costOfMaterial = 1;

	//req resourse
	supply->requaredRes = NO_RES;
	supply->consumeRes = 0;


	// export
	supply->exportable = true;
	supply->exportLimit = PERCENT_25;

	// import
	supply->importable = true;
	supply->importLimit = PERCENT_25;

	supply->displayble = true;
	m_resources[supply->type] = supply;


	/****************************/
	// population

	Resourse* population = new Resourse();
	// values
	population->type = POPULATION;
	population->value = 160;
	population->maxValue = 1000;

	population->hardLimit = true;
	population->sizeOfGroup = GROUP_FROM_16;
	population->producebBy = POPULATION;
	population->producedForGroup = 10;

	// manufacturing for hard res
	population->complexityOfManufacturing = 1;
	population->currentProgress = 0;

	// material
	population->material = SUPPLY;
	population->naturalMaterial = false;
	population->costOfMaterial = MAT_COST_1;

	//req resourse
	population->requaredRes = NO_RES;
	population->consumeRes = 0;

	// export
	population->exportable = false;
	population->exportLimit = 0;

	// import
	population->importable = false;
	population->importLimit = PERCENT_25;

	population->displayble = true;
	m_resources[population->type] = population;

	// sector settings
	m_sector->setFertility(1000);
}

void TestBuilding::setup6Env()
{
	// supply
	Resourse* supply = new Resourse();
	// values
	supply->type = SUPPLY;
	supply->value = 0;
	supply->maxValue = 1000;

	supply->hardLimit = false;
	supply->sizeOfGroup = GROUP_FROM_4;
	supply->producebBy = NO_RES;
	supply->producedForGroup = 0;

	// manufacturing for hard res
	supply->complexityOfManufacturing = 1;
	supply->currentProgress = 0;

	// material
	supply->material = FERTILITY;
	supply->naturalMaterial = true;
	supply->costOfMaterial = 1;

	//req resourse
	supply->requaredRes = NO_RES;
	supply->consumeRes = 0;


	// export
	supply->exportable = false;
	supply->exportLimit = PERCENT_25;

	// import
	supply->importable = false;
	supply->importLimit = PERCENT_25;

	supply->displayble = true;
	m_resources[supply->type] = supply;


	/****************************/
	// population

	Resourse* population = new Resourse();
	// values
	population->type = POPULATION;
	population->value = 150;
	population->maxValue = 1000;

	population->hardLimit = true;
	population->sizeOfGroup = GROUP_FROM_16;
	population->producebBy = NO_RES;
	population->producedForGroup = 0;

	// manufacturing for hard res
	population->complexityOfManufacturing = 1;
	population->currentProgress = 0;

	// material
	population->material = NO_RES;
	population->naturalMaterial = false;
	population->costOfMaterial = MAT_COST_1;

	//req resourse
	population->requaredRes = SUPPLY;
	population->consumeRes = 1;
	population->hardRequirement = true;

	// export
	population->exportable = true;
	population->exportLimit = PERCENT_25;

	// import
	population->importable = false;
	population->importLimit = PERCENT_25;

	population->displayble = true;
	m_resources[population->type] = population;

	// sector settings
	m_sector->setFertility(1000);
}

void TestBuilding::setup7Env()
{
	// TODO
}
/******************************
 * BaseBuildingTester
 * Test case for TestBuilding validation
 *
 *****************************/

BaseBuildingTester::BaseBuildingTester():
	TestCase("Base Building Test")
{
	m_numOfTests = 6;
	PlayerController::getInstance()->addPlayer(Human);
}

void BaseBuildingTester::executeTest(int testNumber)
{
	TestCase::executeTest(testNumber);
	bool res = false;

	switch (testNumber) {
	case 0:
		res = executeT1();
		break;
	case 1:
		res = executeT2();
		break;
	case 2:
		res = executeT3();
		break;
	case 3:
		res = executeT4();
		break;
	case 4:
		res = executeT5();
		break;
	case 5:
		res = executeT6();
		break;
	default:
		break;
	}

	if(res)
		qDebug() << "Test is done";
	else
		qDebug() << "Test is faled!!!";
}

bool BaseBuildingTester::executeT1()
{
	//check base producing functionality
	bool res = true;

	TestBuilding testBuild;
	testBuild.setup1Env();
	testBuild.execResProcess();

	int suppValue = testBuild.getResources(SUPPLY);
	if(suppValue != 190)
	{
		res = false;
	}

	return res;
}

bool BaseBuildingTester::executeT2()
{
	//check hard limit functionality
	bool res = true;

	TestBuilding testBuild;
	testBuild.setup2Env();
	testBuild.execResProcess();

	int suppValue = testBuild.getResources(SUPPLY);
	if(suppValue != 1075)
	{
		res = false;
	}

	return res;
}

bool BaseBuildingTester::executeT3()
{
	// check export functionality
	bool res = true;

	TestBuilding testBuild;
	testBuild.setup3Env();
	testBuild.execResProcess();

	int suppValue = testBuild.getResources(SUPPLY);
	if(suppValue != 1075)
	{
		res = false;
	}

	Player* testPlayer = PlayerController::getInstance()->getPlayer(testBuild.getPlayerID());
	Request * req = testPlayer->getRequest(SUPPLY, PROVIDE, 0, 0);
	if(req == nullptr)
	{
		return false;
	}

	if(req->subject != &testBuild)
	{
		res = false;
	}

	if(req->value != 325)
	{
		res = false;
	}

	return res;
}

bool BaseBuildingTester::executeT4()
{
	// check import functionality
	bool res = true;

	TestBuilding testBuild;
	testBuild.setup4Env();
	testBuild.execResProcess();

	int suppValue = testBuild.getResources(SUPPLY);
	if(suppValue != 100)
	{
		res = false;
	}

	Player* testPlayer = PlayerController::getInstance()->getPlayer(testBuild.getPlayerID());
	Request * req = testPlayer->getRequest(SUPPLY, CONSUME, 0, 0);
	if(req == nullptr)
	{
		return false;
	}

	if(req->subject != &testBuild)
	{
		res = false;
	}

	if(req->value != 150)
	{
		res = false;
	}

	return res;
}

bool BaseBuildingTester::executeT5()
{
	// check import functionality
	bool res = true;

	TestBuilding testBuild;
	testBuild.setup5Env();
	testBuild.execResProcess();

	int popValue = testBuild.getResources(POPULATION);
	if(popValue != 210)
	{
		res = false;
	}

	int suppValue = testBuild.getResources(SUPPLY);
	if(suppValue != 0)
	{
		res = false;
	}

	return res;
}


bool BaseBuildingTester::executeT6()
{
	// check import functionality
	bool res = true;

	TestBuilding testBuild;
	testBuild.setup6Env();
	testBuild.execResProcess();

	int popValue = testBuild.getResources(POPULATION);
	if(popValue != 113)
	{
		res = false;
	}

	Player* testPlayer = PlayerController::getInstance()->getPlayer(testBuild.getPlayerID());
	Request * req = testPlayer->getRequest(POPULATION, PROVIDE, 0, 0);
	if(req == nullptr)
	{
		return false;
	}

	if(req->subject != &testBuild)
	{
		res = false;
	}

	if(req->value != 113)
	{
		res = false;
	}

	return res;
}
