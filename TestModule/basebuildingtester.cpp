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
}

void TestBuilding::setup2Env()
{
	//TODO
}

void TestBuilding::setup3Env()
{
	//TODO
}

/******************************
 * BaseBuildingTester
 * Test case for TestBuilding validation
 *
 *****************************/

BaseBuildingTester::BaseBuildingTester():
	TestCase("BaseBuildingTester")
{
	m_numOfTests = 1;
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
	default:
		break;
	}

	if(res)
		qDebug() << "Test is done";
	else
		qDebug() << "Test is faled";
}

bool BaseBuildingTester::executeT1()
{
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
	return true;
}

bool BaseBuildingTester::executeT3()
{
	return true;
}

bool BaseBuildingTester::executeT4()
{
	return true;
}
