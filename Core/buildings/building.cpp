#include "building.h"
#include "Core/gobjwrapper.h"
#include "Core/objectstatecontroller.h"
#include "Core/playercontroller.h"
#include "qdebug.h"


Building::Building(GObjWrapper *wrapper, Sector* sector, int initialStep, int plID):
	GObject(wrapper),
	m_sector(sector),
	m_initialStep(initialStep),
	m_maxLevel(0),
	m_stateCount(0)
{    
	m_level = 1;
	m_playerID = plID;
	m_player = PlayerController::getInstance()->getPlayer(m_playerID);
	setMapCoord(sector->getMapX(), sector->getMapY());
	m_wrapper->setMarker(m_playerID);
}

Building::~Building()
{

}


void Building::process(int step)
{
	if(step != m_initialStep)
		return;

	processResource();

	m_stateCount++;
	if(m_stateCount >= 5)
	{
		checkState();
		m_stateCount = 0;
	}
}

void Building::processResource()
{
	// process all registred resourses
	RESOURSES resType;
	Resourse resorce;

	// start new iteration
	resetIteration();
	while (getNextResource(resType, resorce))
	{
		// take current value of material
		int currentValue = resorce.value;
		int possibleToProduce = 0;

		// determine - who will be produce this resource and working efficiency of group
		RESOURSES workerType = resorce.producebBy;

		// check - should we produce current resource here
		if(workerType != NO_RES)
		{
			int producedForGroup = resorce.producedForGroup;

			Resourse* workerResObj = getResourcesObj(workerType);

			if(workerResObj == nullptr)
			{
				qDebug() << "Building::processResource: Error! workerResObj is nullptr";
				continue;
			}

			int sizeOfWorkerGroup = workerResObj->sizeOfGroup;

			int workers = workerResObj->value;
			if(workers == INVALIDE_VALUE)
			{
				qDebug() << "Building::processResource: Error! workers = INVALIDE_VALUE";
				continue;
			}

			// calculate - how much resourses(works) we can produce at this step
			possibleToProduce = (workers >> sizeOfWorkerGroup) * producedForGroup;
		}



		//check resourse storage limit
		int storageLimit = (resorce.maxValue - currentValue) * resorce.complexityOfManufacturing - resorce.currentProgress;
		if(possibleToProduce > storageLimit && resorce.hardLimit)
		{
			possibleToProduce = storageLimit;
		}


		/* **************************************** */
		// material part
		RESOURSES materialType = resorce.material;
		if(materialType != NO_RES)
		{
			// if material is natural resourse - take it from sector
			int materialStorage = INVALIDE_VALUE;
			if(resorce.naturalMaterial)
			{
				materialStorage = m_sector->getNaturalResourse(materialType);
			}
			else
			{
				// if it synthetic - take it from storage
				materialStorage = getResources(materialType);
			}

			int sufficientTo = materialStorage >> resorce.costOfMaterial;

			// check - are we have enough resourse?
			if(possibleToProduce > sufficientTo)
			{
				// determine how much we can produce by this material
				possibleToProduce = sufficientTo;
			}

			// if material is synthetic - decrease value by used
			if(!resorce.naturalMaterial)
			{
				materialStorage = materialStorage - (possibleToProduce << resorce.costOfMaterial);
				setResources(materialType, materialStorage);
			}
		}



		/* **************************************** */
		//produce resource(works)
		int currWork = resorce.currentProgress + possibleToProduce;
		int producedResource = currWork / resorce.complexityOfManufacturing;
		int newCurrentProgress = currWork % resorce.complexityOfManufacturing;

		// setup new value of progress
		setResProgress(resType, newCurrentProgress);

		int newResValue = currentValue + producedResource;



		/* **************************************** */
		// TODO - think about siquence and resourse optimization
		// supply part
		bool reqResIsEnough = true;
		int resWithoutSupply = 0;

		if(resorce.requaredRes != NO_RES)
		{
			if(resorce.consumeRes == 0)
			{
				qDebug() << "Building::processResource: Error! resorce.consumeRes is 0!!! for res: " << resorce.type;
				return;
			}

			int reqResStorage = getResources(resorce.requaredRes);
			int numOfResWithSupply = reqResStorage / resorce.consumeRes;

			if(newResValue > numOfResWithSupply)
			{
				if(resorce.hardRequirement)
				{
					// 25% of res without supply (overflow) should be destroyed
					resWithoutSupply = newResValue - numOfResWithSupply;
					int resToDestroy = resWithoutSupply >> 2;
					newResValue -= resToDestroy;
					resWithoutSupply -= resToDestroy;
				}
				reqResStorage = 0;
				reqResIsEnough = false;

			}
			else
			{
				reqResStorage -= newResValue * resorce.consumeRes;
			}

			//setup new value of "supply" resourse
			setResources(resorce.requaredRes, reqResStorage);
		}


		/* **************************************** */
		// storage limit part
		if(!resorce.hardLimit)
		{
			if(newResValue > resorce.maxValue)
			{
				// 25% of res without supply (overflow) should be destroyed
				int resToDestroy = (newResValue - resorce.maxValue) >> 2;
				newResValue -= resToDestroy;
				resWithoutSupply -= resToDestroy;
			}
		}


		// Setup new value of produced resource
		setResources(resType, newResValue);

		// check import
		if(resorce.importable && reqResIsEnough)
		{
			int limit = resorce.maxValue;
			int lowLimit = limit >> resorce.importLimit;	// take low limit

			if(lowLimit > newResValue)
			{
				setNewRequestToMap(CONSUME, resType, lowLimit - newResValue);
			}
		}

		// check export
		if(resorce.exportable)
		{
			int limit = resorce.maxValue;
			int topLimit = limit - (limit >> resorce.exportLimit);	// take top limit

			if(topLimit < newResValue || resWithoutSupply > 0)
			{
				int extraRes = newResValue - topLimit;
				int resToExport = resWithoutSupply > extraRes ? resWithoutSupply: extraRes;
				setNewRequestToMap(PROVIDE, resType, resToExport);
			}
		}
	}
}

void Building::setNewRequestToMap(REQ_TYPE reqType, RESOURSES resType, int value)
{
	Request * req = m_requestMap[resType];

	if(value > 0)
	{
		if(req == nullptr)
		{
			req = new Request();
			req->resType = resType;
			req->status = AWAITS;
			req->subject = this;
			req->type = reqType;
			req->value = value;

			m_requestMap[resType] = req;
		}

		if(req->type != reqType)
		{
			qDebug() << "setNewRequestToMap: Change req-direction at x:" << getMapX() << " y:" << getMapY();

			// set NOT_ACTUAL for previus request
			req->status = NOT_ACTUAL;
			req->value = 0;

			//create new request
			req = new Request();
			req->resType = resType;
			req->status = AWAITS;
			req->subject = this;
			req->type = reqType;
			req->value = value;
			m_requestMap[resType] = req;
		}


		if(req->value < value)
		{
			req->value = value;
		}

		//register request if it needed
		if(req->value >= HUMAN_MIN_RES_TO_MOVE && !req->registred)
		{
			m_player->addRequest(req);
		}
	}
}


void Building::checkState()
{
	int infrostructure = getResources(INFROSTRUCTURE);
	int topInfLevel = getResLimit(INFROSTRUCTURE);
	int lowInfLevel = m_player->getResLimit(m_type, INFROSTRUCTURE, m_level);

	int currentLevel = m_level;

	// check to increae level
    UI_STATES ui_state = INVALID_UI_STATE;
	if(infrostructure >= topInfLevel && m_level < m_maxLevel)
	{
		m_level++;
        ui_state = UI_BUILDED;
	}
	// chack to degrise level
	else if(infrostructure < lowInfLevel && m_level > 0)
	{
		m_level--;
        ui_state = UI_DESTROYED;
	}

	if(currentLevel != m_level)
	{
		RESOURSES resType;
		Resourse value;

		GObject::resetIteration();

		while(this->getNextResource(resType, value))
		{
			updateResourse(resType, m_level);
		}

        m_wrapper->setLevel(m_level, ui_state);
	}
}

void Building::deactivate()
{
	if(m_wrapper != nullptr)
	{
		m_wrapper->setMarker(INVALIDE_VALUE);
	}

	GObject::deactivate();
}

void Building::activate()
{
	m_wrapper->setEnabled();
	m_wrapper->setLevel(0, UI_NORMAL);
	m_wrapper->setType(m_type);
}

/************************************************
 * Func: removeWrapper
 * Desc: Remove wrapper from building.
 * Note: Used for updating process to save wrapper active
 *		 Also we should disable this object
 ***********************************************/
void Building::removeWrapper()
{
	ObjectStateController::getInstance()->setGObjectCondition(m_id, DESTROED_CONDITION);
	m_active = false;
	m_wrapper = nullptr;
}

/************************************************
 * Func: takeDamage
 * Desc: Building take demage
 ***********************************************/
void Building::takeDamage(int damage)
{
	int infrStruct = getResources(INFROSTRUCTURE);
	int population = getResources(POPULATION);

	population -= damage;
	if(population < 0)
	{
		population = 0;
	}

	infrStruct -= (damage / 2);
	if(infrStruct < 0)
	{
		infrStruct = 0;
		ObjectStateController::getInstance()->setGObjectCondition(m_id, DESTROED_CONDITION);
	}

	setResources(INFROSTRUCTURE, infrStruct);
	setResources(POPULATION, population);
}
