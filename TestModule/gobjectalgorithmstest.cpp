#include "gobjectalgorithmstest.h"
#include "Core/gobject.h"
#include "Core/player/requestmanager.h"
#include "Core/goalgorithms.h"
#include "Core/objectstatecontroller.h"
#include "qdebug.h"

TestGObject::TestGObject(GObjWrapper *wrapper):
	GObject(wrapper)
{

}

void TestGObject::addResourseToMap(Resourse *res)
{
	m_resources[res->type] = res;
	m_requestMap[res->type] = nullptr;
}

GObjectAlgorithmsTest::GObjectAlgorithmsTest():
	TestCase("GObject Algorithms Test")
{
	m_numOfTests = 5;
}

void GObjectAlgorithmsTest::executeTest(int testNumber)
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
	default:
		break;
	}

	if(res)
		qDebug() << "Test is done";
	else
		qDebug() << "Test is faled";
}

bool GObjectAlgorithmsTest::executeT1()
{
	bool result = true;
	TestGObject* sender = new TestGObject();
	TestGObject* reciever = new TestGObject();

	ObjectStateController* stateController = ObjectStateController::getInstance();
	sender->setID(stateController->getNewGObjectID());
	stateController->addGObject(sender->getID());
	reciever->setID(stateController->getNewGObjectID());
	stateController->addGObject(reciever->getID());

	Request* senderReq = new Request();
	senderReq->registred = true;
	senderReq->resType = POPULATION;
	senderReq->status = AWAITS;
	senderReq->subject = sender;
	senderReq->type = PROVIDE;
	senderReq->value = 1000;

	Request* recieverReq = new Request();
	memcpy(recieverReq, senderReq, sizeof(Request));
	recieverReq->type = CONSUME;
	recieverReq->subject = reciever;

	Resourse* senderRes = new Resourse();
	senderRes->type = POPULATION;
	senderRes->value = 2000;
	senderRes->maxValue = 5000;

	Resourse* recieverRes = new Resourse();
	recieverRes->type = POPULATION;
	recieverRes->value = 0;
	recieverRes->maxValue = 5000;

	sender->addResourseToMap(senderRes);
	sender->addRequst(senderReq);

	reciever->addResourseToMap(recieverRes);
	reciever->addRequst(recieverReq);

	GOAlgorithms::transferResourceByRequest(sender, reciever, POPULATION);

	if(sender->getResources(POPULATION) != 1000)
	{
		qDebug("Stage 1 faled");
		result = false;
	}

	if(reciever->getResources(POPULATION) != 1000)
	{
		qDebug("Stage 2 faled");
		result = false;
	}

	if(sender->getRequest(POPULATION) != nullptr)
	{
		qDebug("Stage 3 faled");
		result = false;
	}

	if(reciever->getRequest(POPULATION) != nullptr)
	{
		qDebug("Stage 4 faled");
		result = false;
	}


	delete sender;
	delete reciever;

	return result;
}


bool GObjectAlgorithmsTest::executeT2()
{
	bool result = true;
	TestGObject* sender = new TestGObject();
	TestGObject* reciever = new TestGObject();

	ObjectStateController* stateController = ObjectStateController::getInstance();
	sender->setID(stateController->getNewGObjectID());
	stateController->addGObject(sender->getID());
	reciever->setID(stateController->getNewGObjectID());
	stateController->addGObject(reciever->getID());

	Request* senderReq = new Request();
	senderReq->registred = true;
	senderReq->resType = POPULATION;
	senderReq->status = AWAITS;
	senderReq->subject = sender;
	senderReq->type = PROVIDE;
	senderReq->value = 1000;

	Request* recieverReq = new Request();
	memcpy(recieverReq, senderReq, sizeof(Request));
	recieverReq->type = CONSUME;
	recieverReq->subject = reciever;

	Resourse* senderRes = new Resourse();
	senderRes->type = POPULATION;
	senderRes->value = 500;
	senderRes->maxValue = 5000;

	Resourse* recieverRes = new Resourse();
	recieverRes->type = POPULATION;
	recieverRes->value = 700;
	recieverRes->maxValue = 5000;

	sender->addResourseToMap(senderRes);
	sender->addRequst(senderReq);

	reciever->addResourseToMap(recieverRes);
	reciever->addRequst(recieverReq);

	GOAlgorithms::transferResourceByRequest(sender, reciever, POPULATION);

	if(sender->getResources(POPULATION) != 0)
	{
		qDebug("Stage 1 faled");
		result = false;
	}

	if(reciever->getResources(POPULATION) != 1200)
	{
		qDebug("Stage 2 faled");
		result = false;
	}

	if(sender->getRequest(POPULATION) == nullptr)
	{
		qDebug("Stage 3 faled");
		result = false;
	}

	if(reciever->getRequest(POPULATION) == nullptr)
	{
		qDebug("Stage 4 faled");
		result = false;
	}

	delete sender;
	delete reciever;

	return result;
}


// NEGATIVE TEST!
bool GObjectAlgorithmsTest::executeT3()
{
	qDebug() << "NEGATIVE TEST!";

	bool result = true;
	TestGObject* sender = new TestGObject();
	TestGObject* reciever = new TestGObject();

	ObjectStateController* stateController = ObjectStateController::getInstance();
	sender->setID(stateController->getNewGObjectID());
	stateController->addGObject(sender->getID());
	reciever->setID(stateController->getNewGObjectID());
	stateController->addGObject(reciever->getID());

	Request* senderReq = new Request();
	senderReq->registred = true;
	senderReq->resType = POPULATION;
	senderReq->status = AWAITS;
	senderReq->subject = sender;
	senderReq->type = PROVIDE;
	senderReq->value = 1000;

	Request* recieverReq = new Request();
	memcpy(recieverReq, senderReq, sizeof(Request));
	recieverReq->type = PROVIDE;	// FAIL CONDITION!
	recieverReq->subject = reciever;

	Resourse* senderRes = new Resourse();
	senderRes->type = POPULATION;
	senderRes->value = 500;
	senderRes->maxValue = 5000;

	Resourse* recieverRes = new Resourse();
	recieverRes->type = POPULATION;
	recieverRes->value = 700;
	recieverRes->maxValue = 5000;

	sender->addResourseToMap(senderRes);
	sender->addRequst(senderReq);

	reciever->addResourseToMap(recieverRes);
	reciever->addRequst(recieverReq);

	int transfRes = GOAlgorithms::transferResourceByRequest(sender, reciever, POPULATION);

	if(transfRes != INVALIDE_VALUE)
	{
		qDebug("Stage 0 faled");
		result = false;
	}

	if(sender->getResources(POPULATION) != 500)
	{
		qDebug("Stage 1 faled");
		result = false;
	}

	if(reciever->getResources(POPULATION) != 700)
	{
		qDebug("Stage 2 faled");
		result = false;
	}

	if(sender->getRequest(POPULATION) == nullptr)
	{
		qDebug("Stage 3 faled");
		result = false;
	}

	if(reciever->getRequest(POPULATION) == nullptr)
	{
		qDebug("Stage 4 faled");
		result = false;
	}

	delete sender;
	delete reciever;

	return result;
}

// NEGATIVE TEST!
bool GObjectAlgorithmsTest::executeT4()
{
	qDebug() << "NEGATIVE TEST!";

	bool result = true;
	TestGObject* sender = nullptr;
	TestGObject* reciever = nullptr;

	int transfRes = GOAlgorithms::transferResourceByRequest(sender, reciever, POPULATION);

	if(transfRes != INVALIDE_VALUE)
	{
		qDebug("Stage 0 faled");
		result = false;
	}

	return result;
}



bool GObjectAlgorithmsTest::executeT5()
{
	bool result = true;
	TestGObject* sender = new TestGObject();
	TestGObject* reciever = new TestGObject();

	ObjectStateController* stateController = ObjectStateController::getInstance();
	sender->setID(stateController->getNewGObjectID());
	stateController->addGObject(sender->getID());
	reciever->setID(stateController->getNewGObjectID());
	stateController->addGObject(reciever->getID());

	Request* senderReq = new Request();
	senderReq->registred = true;
	senderReq->resType = POPULATION;
	senderReq->status = AWAITS;
	senderReq->subject = sender;
	senderReq->type = PROVIDE;
	senderReq->value = 1000;

	Request* recieverReq = new Request();
	memcpy(recieverReq, senderReq, sizeof(Request));
	recieverReq->type = CONSUME;
	recieverReq->subject = reciever;

	Resourse* senderRes = new Resourse();
	senderRes->type = POPULATION;
	senderRes->value = 4000;
	senderRes->maxValue = 5000;

	Resourse* recieverRes = new Resourse();
	recieverRes->type = POPULATION;
	recieverRes->value = 4500;
	recieverRes->maxValue = 5000;

	sender->addResourseToMap(senderRes);
	sender->addRequst(senderReq);

	reciever->addResourseToMap(recieverRes);
	reciever->addRequst(recieverReq);

	int transfRes = GOAlgorithms::transferResourceByRequest(sender, reciever, POPULATION);

	if(transfRes != 500)
	{
		qDebug("Stage 0 faled");
		result = false;
	}

	if(sender->getResources(POPULATION) != 3500)
	{
		qDebug("Stage 1 faled");
		result = false;
	}

	if(reciever->getResources(POPULATION) != 5000)
	{
		qDebug("Stage 2 faled");
		result = false;
	}

	if(sender->getRequest(POPULATION) == nullptr)
	{
		qDebug("Stage 3 faled");
		result = false;
	}

	if(reciever->getRequest(POPULATION) == nullptr)
	{
		qDebug("Stage 4 faled");
		result = false;
	}

	delete sender;
	delete reciever;

	return result;
}
