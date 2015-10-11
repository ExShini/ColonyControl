#include "testmanager.h"
#include "requestmanagertest.h"
#include "qdebug.h"

TestManager::TestManager()
{

}

void TestManager::exec()
{
	RequestManagerTest test1;
	/***********************/

	if(test1.executeT1())
		qDebug() << "Test is done";
	else
		qDebug() << "Test is faled";

	/***********************/
	if(test1.executeT2())
		qDebug() << "Test is done";
	else
		qDebug() << "Test is faled";

	/***********************/
	if(test1.executeT3())
		qDebug() << "Test is done";
	else
		qDebug() << "Test is faled";


	/***********************/
	if(test1.executeT4())
		qDebug() << "Test is done";
	else
		qDebug() << "Test is faled";
}
