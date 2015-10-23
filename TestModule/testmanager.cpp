#include "testmanager.h"
#include "requestmanagertest.h"
#include "basebuildingtester.h"
#include "qdebug.h"

TestManager::TestManager()
{

}

void TestManager::exec()
{
	qDebug() << "\n*** Start testing ***\n";
	RequestManagerTest testCase1;
	/***********************/
	for(int i = 0; i < testCase1.getNumOfTests(); i++)
	{
		testCase1.executeTest(i);
	}

	qDebug() << "\n*** Next test case ***\n";

	BaseBuildingTester testCase2;
	/***********************/
	for(int i = 0; i < testCase2.getNumOfTests(); i++)
	{
		testCase2.executeTest(i);
	}

}
