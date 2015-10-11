#include "requestmanagertest.h"
#include "Core/player/requestmanager.h"
#include "Core/gobject.h"
#include "qdebug.h"

RequestManagerTest::RequestManagerTest()
{

}

bool RequestManagerTest::executeT1()
{
	bool status = true;

	RequestManager reqManager;

	GObject* obj = new GObject(nullptr);
	obj->setMapCoord(5,5);


	// add 10 CONSUME request
	for(int i = 0; i < 10 ; i++)
	{
		Request* req = new Request();
		req->resType = POPULATION;
		req->status = AWAITS;
		req->subject = obj;
		req->type = CONSUME;
		req->value = 100 + i;

		reqManager.addRequest(req);
	}

	// check requests
	for(int i = 0; i < 10; i++)
	{
		Request* req = reqManager.findRequest(POPULATION, CONSUME, 5, 5);

		if(req == nullptr)
		{
			status = false;
			break;
		}

		if(req->resType != POPULATION)
		{
			qDebug() << "Error! req->resType";
			status = false;
		}

		if(req->status != AWAITS)
		{
			qDebug() << "Error! req->status";
			status = false;
		}

		if(req->subject != obj)
		{
			qDebug() << "Error! req->subject";
			status = false;
		}

		if(req->type != CONSUME)
		{
			qDebug() << "Error! req->type";
			status = false;
		}

		if(req->value != 100 + i)
		{
			qDebug() << "Error! req->value";
			status = false;
		}
	}


	return status;
}


bool RequestManagerTest::executeT2()
{
	bool status = true;

	RequestManager reqManager;

	GObject* obj = new GObject(nullptr);
	obj->setMapCoord(5,5);


	// add 10 CONSUME request
	for(int i = 0; i < 10 ; i++)
	{
		Request* req = new Request();
		req->resType = POPULATION;
		req->status = AWAITS;
		req->subject = obj;
		req->type = CONSUME;
		req->value = 100 + i;

		reqManager.addRequest(req);
	}

	// check requests
	for(int i = 0; i < 10; i++)
	{
		Request* req = reqManager.findRequest(POPULATION, PROVIDE, 5, 5);

		if(req != nullptr)
		{
			status = false;
			break;
		}
	}

	return status;
}


bool RequestManagerTest::executeT3()
{
	bool status = true;

	RequestManager reqManager;

	GObject* obj = new GObject(nullptr);
	obj->setMapCoord(0,0);


	// add 10 CONSUME request
	for(int i = 0; i < 10 ; i++)
	{
		Request* req = new Request();
		req->resType = POPULATION;
		req->status = AWAITS;
		req->subject = obj;
		req->type = CONSUME;
		req->value = 100 + i;

		reqManager.addRequest(req);
	}

	// check requests
	for(int i = 0; i < 10; i++)
	{
		Request* req = reqManager.findRequest(POPULATION, CONSUME, 16, 16);

		if(req != nullptr)
		{
			status = false;
			break;
		}
	}

	return status;
}


bool RequestManagerTest::executeT4()
{
	bool status = true;

	RequestManager reqManager;

	GObject* obj = new GObject(nullptr);
	obj->setMapCoord(0,0);


	// add 10 CONSUME request
	for(int i = 0; i < 10 ; i++)
	{
		Request* req = new Request();
		req->resType = POPULATION;
		req->status = AWAITS;
		req->subject = obj;
		req->type = CONSUME;
		req->value = 100 + i;

		reqManager.addRequest(req);
	}

	// check requests
	for(int i = 0; i < 10; i++)
	{
		Request* req = reqManager.findRequest(POPULATION, PROVIDE, 16, 16);

		if(req != nullptr)
		{
			status = false;
			break;
		}
	}

	return status;
}
