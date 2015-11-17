#include "goalgorithms.h"
#include "gobject.h"
#include "Enums/objstatus.h"
#include "objectstatecontroller.h"
#include "Core/player/requestmanager.h"

#include "qdebug.h"

GOAlgorithms::GOAlgorithms()
{

}

int GOAlgorithms::transferResourceByRequest(GObject *sender, GObject *receiver, RESOURSES resType)
{
	if(sender == nullptr)
	{
		qDebug() << "GOAlgorithms::transferResourceByRequest: sender is null!";
		return INVALIDE_VALUE;
	}

	if(receiver == nullptr)
	{
		qDebug() << "GOAlgorithms::transferResourceByRequest: receiver is null!";
		return INVALIDE_VALUE;
	}

	ObjectStateController* stateCntr = ObjectStateController::getInstance();
	int destrState = DESTROED_CONDITION | IN_DESTRUCTION;
	bool isActive = !stateCntr->chackGObjectCondition(sender->getID(), destrState);

	if(!isActive)
	{
		qDebug() << "GOAlgorithms::transferResourceByRequest: ERROR! sender destroed!";
		return INVALIDE_VALUE;
	}

	isActive = !stateCntr->chackGObjectCondition(receiver->getID(), destrState);

	if(!isActive)
	{
		// in some case receiver can be destroued
		return INVALIDE_VALUE;
	}

	Request* senderReq = sender->getRequest(resType);
	Request* receiverReq = receiver->getRequest(resType);

	if(senderReq == nullptr || receiverReq == nullptr)
	{
		qDebug() << "GOAlgorithms::transferResourceByRequest: can not transfer res! Request is null";
		return INVALIDE_VALUE;
	}

	if(senderReq->status == NOT_ACTUAL)
	{
		qDebug() << "GOAlgorithms::transferResourceByRequest: senderReq is NOT_ACTUAL!";

		// delete bad request and notify sender
		delete senderReq;
		sender->requestComplited(resType);
		return INVALIDE_VALUE;
	}

	if(receiverReq->status == NOT_ACTUAL)
	{
		// in some case receiver can change request "direction"
		return INVALIDE_VALUE;
	}

	if(senderReq->type != PROVIDE || receiverReq->type != CONSUME)
	{
//		qDebug() << "GOAlgorithms::transferResourceByRequest: ERROR! request types are wrong!"
//					" senderReq->type = " <<  senderReq->type <<
//					" receiverReq->type = " << receiverReq->type;
		return INVALIDE_VALUE;
	}

	// take current values and limits
	int maxRecieverValue = receiver->getResLimit(resType);
	int currRecValue = receiver->getResources(resType);
	int storSize = maxRecieverValue - currRecValue;

	int currSendValue = sender->getResources(resType);

	// next step - determine how much resourses we can transfer
	int resToTransfer = INVALIDE_VALUE;
	int resToProvide = senderReq->value < currSendValue ? senderReq->value : currSendValue;
	int resToConsume = receiverReq->value > storSize ? storSize : receiverReq->value;


	// determine minumum form send and consume values
	resToTransfer = resToProvide > resToConsume ? resToConsume : resToProvide;

	// next step - transfer resourse
	currRecValue += resToTransfer;
	currSendValue -= resToTransfer;

	// setup new res value and update requests
	receiver->setResources(resType, currRecValue);
	sender->setResources(resType, currSendValue);

	receiverReq->value -= resToTransfer;
	senderReq->value -= resToTransfer;

	// check request
	if(receiverReq->value == 0)
	{
		receiver->requestComplited(resType);
		delete receiverReq;
	}

	// check request
	if(senderReq->value == 0)
	{
		sender->requestComplited(resType);
		delete senderReq;
	}

	return resToTransfer;

}
