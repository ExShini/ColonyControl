#include "unitcontroller.h"
#include "UIDrawer/UIElements/uiunitcontroller.h"
#include "UIDrawer/UIElements/uiunitcntr.h"
#include "Core/objectstatecontroller.h"
#include "Core/objectcontroller.h"
#include "Core/buildings/building.h"
#include "QThread"

UnitController* UnitController::s_instance = nullptr;

UnitController::UnitController(QObject *parent):
	QObject(parent),
	m_units(),
	m_freeWrappers(),
	m_inUseWrappers()
{
}

UnitController::~UnitController()
{

}


UnitController* UnitController::getInstance()
{
	if(s_instance == nullptr)
	{
		s_instance = new UnitController();
	}

	return s_instance;
}

void UnitController::init()
{
	//connect wrappers to UI part
	UiUnitController* uiUnCntr = UiUnitController::getInstance();

	qDebug() << "Connecting units!";
	for(int i = 0; i < MAX_NUMBER_OF_UNITS; i++)
	{

		QThread* targetTread = this->thread();
		UnitWrapper* wrapper = new UnitWrapper();
		wrapper->moveToThread(targetTread);
		UiUnitCntr* uc = uiUnCntr->getUnitCntr(i);

		QObject::connect(wrapper, SIGNAL(changeType(int)),
						 uc, SLOT(setType(int)), Qt::QueuedConnection);
		QObject::connect(wrapper, SIGNAL(changeLevel(int, int)),
						 uc, SLOT(setLevel(int, int)), Qt::QueuedConnection);
		QObject::connect(wrapper, SIGNAL(enable()),
						 uc, SLOT(enableObj()), Qt::QueuedConnection);
		QObject::connect(wrapper, SIGNAL(disable()),
						 uc, SLOT(disableObj()), Qt::QueuedConnection);
		QObject::connect(wrapper, SIGNAL(posChanged(int,int)),
						 uc, SLOT(setPosition(int,int)), Qt::QueuedConnection);
		QObject::connect(wrapper, SIGNAL(directionChanged(int)),
						 uc, SLOT(setDirection(int)), Qt::QueuedConnection);

		m_wrappers[i] = wrapper;
		m_freeWrappers.push_back(wrapper);

		m_statusController = ObjectStateController::getInstance();
	}


	qDebug() << "Connecting units is done!";
}

void UnitController::setupNewGame()
{
	//clear all buffers
	m_units.clearAll();
}

void UnitController::process(int step)
{
	//start new iteration
	m_units.startIter();

	Unit* unit = (Unit*)m_units.nextEl();
	int oldx = INVALIDE_VALUE;
	int oldy = INVALIDE_VALUE;
	int id = INVALIDE_VALUE;

	//process all buildings
	while(unit != nullptr)
	{

		id = unit->getID();
		bool isActive = !m_statusController->chackGObjectCondition(id, DESTROED_CONDITION);

		if(isActive)
		{
			unit->process(step);
			if(unit->isItChangePosition(oldx, oldy))
			{
				m_units.moveElementFrom(unit, oldx, oldy);
				unit->unitWasMoved();
			}
		}

		unit = (Unit*)m_units.nextEl();
	}
}

void UnitController::finalizeStep()
{
	//finalize iteration
	m_units.finilizeProc();
}

Unit* UnitController::buildUnit(Building *base, OBJECT_TYPE unitType)
{
	Unit* unit = nullptr;
	UnitWrapper* wrapper = nullptr;

	if(m_freeWrappers.count())
	{
		wrapper = m_freeWrappers.front();
		m_freeWrappers.pop_front();
	}
	else
	{
		qDebug() << "UnitController::buildUnit: ERROR! we doesn't have enough wrappers!!!";
		return nullptr;
	}

	int playerId = base->getPlayerID();
	UnitFactory* factory = m_unitFactories[playerId];

	if(factory != nullptr)
	{
		unit = factory->buildUnit(unitType, base, wrapper);

		int unitID = ObjectStateController::getInstance()->getNewGObjectID();
		unit->setID(unitID);
		ObjectStateController::getInstance()->addGObject(unitID);
	}
	else
	{
		qDebug() << "UnitController::buildUnit: ERROR! factory for player: " << playerId << " is null!";
		return nullptr;
	}


	if(unit != nullptr)
	{
		m_units.addEl(unit);
	}

	return unit;
}


Unit* UnitController::buildAbilityExecutor(int playerID, OBJECT_TYPE unitType)
{
	Unit* unit = nullptr;
	UnitWrapper* wrapper = nullptr;

	if(m_freeWrappers.count())
	{
		wrapper = m_freeWrappers.front();
		m_freeWrappers.pop_front();
	}
	else
	{
		qDebug() << "UnitController::buildAbilityExecutor: ERROR! we doesn't have enough wrappers!!!";
		return nullptr;
	}

	UnitFactory* factory = m_unitFactories[playerID];

	if(factory != nullptr)
	{
		unit = factory->buildUnit(unitType, nullptr, wrapper);	// ability have not base

		int unitID = ObjectStateController::getInstance()->getNewGObjectID();
		unit->setID(unitID);
		ObjectStateController::getInstance()->addGObject(unitID);
	}
	else
	{
		qDebug() << "UnitController::buildAbilityExecutor: ERROR! factory for player: " << playerID << " is null!";
		return nullptr;
	}


	if(unit != nullptr)
	{
		m_units.addEl(unit);
	}

	return unit;
}


void UnitController::addUnitFactory(UnitFactory *factory, int playerID)
{
	if(factory == nullptr)
	{
		qDebug() << "UnitController::addUnitFactory : null factory";
		return;
	}

	if(playerID < 0 || playerID >= NUMBER_OF_PLAYERS)
	{
		qDebug() << "UnitController::addUnitFactory : incorrect player id : " << playerID;
		return;
	}

	m_unitFactories[playerID] = factory;
}


void UnitController::returnUnitWrapper(UnitWrapper *wrapper)
{
	m_freeWrappers.push_back(wrapper);
}
