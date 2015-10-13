#include "testmanager.h"
#include "requestmanagertest.h"
#include "qdebug.h"

TestManager::TestManager()
{

}

void TestManager::exec()
{
	RequestManagerTest testCase1;
	/***********************/
	for(int i = 0; i < testCase1.getNumOfTests(); i++)
	{
		testCase1.executeTest(i);
	}


}
