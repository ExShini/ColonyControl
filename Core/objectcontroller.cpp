#include "objectcontroller.h"
#include "buildings/human/humsettlers.h"
#include "buildings/human/humcolonycenter.h"
#include "qdebug.h"
#include "Enums/coresettings.h"
#include "UIDrawer/UIElements/uimapcontroller.h"
#include "UIDrawer/UIElements/monitorpanelcontroller.h"
#include "objectstatecontroller.h"
#include "QThread"

ObjectController* ObjectController::s_instance = nullptr;


/************************************************
 * Func: ObjectController(QObject *parent)
 * Desc: Constructor.
 ***********************************************/
ObjectController::ObjectController(QObject *parent):
    QObject(parent),
	m_buildings(),
	m_xFocus(0),
	m_yFocus(0),
	m_initialCounter(0),
	m_objectID(0)
{
    for(int i = 0; i < MAP_WIDTH; i++)
    {
        for(int j = 0; j < MAP_HEIGHT; j++)
        {
            m_wrappers[i][j] = nullptr;
			m_sectors[i][j] = new Sector();
			m_sectors[i][j]->setMapCoord(i, j);
        }
    }

	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		m_buildFactory[i] = nullptr;
	}

	m_mapGenerator = new MapGenerator();
}

/************************************************
 * Func: ~ObjectController
 * Desc: Destructor.
 ***********************************************/
ObjectController::~ObjectController()
{

}

/************************************************
 * Func: getInstance
 * Desc: Singliton implementation.
 ***********************************************/
ObjectController* ObjectController::getInstance()
{
	if(s_instance == nullptr)
    {
		s_instance = new ObjectController();
    }
	return s_instance;
}

/************************************************
 * Func: init
 * Desc: Initializing of ObjectController.
 ***********************************************/
void ObjectController::init()
{
    //connect wrappers to UI part
    UIMapController* uiMap = UIMapController::getInstance();

    qDebug() << "Connecting!";
    for(int i = 0; i < MAP_WIDTH; i++)
    {
        for(int j = 0; j < MAP_HEIGHT; j++)
        {
			QThread* targetThread = this->thread();
            GObjWrapper* wrapper = new GObjWrapper();
			wrapper->moveToThread(targetThread);
            CellController* cc = uiMap->getCCntrByCor(i, j);

            QObject::connect(wrapper, SIGNAL(changeType(int)),
                             cc, SLOT(setType(int)), Qt::QueuedConnection);
			QObject::connect(wrapper, SIGNAL(changeLevel(int, int)),
							 cc, SLOT(setLevel(int, int)), Qt::QueuedConnection);
			QObject::connect(wrapper, SIGNAL(changeMarker(int)),
							 cc, SLOT(setPlayerMarker(int)), Qt::QueuedConnection);
            QObject::connect(wrapper, SIGNAL(enable()),
                             cc, SLOT(enableObj()), Qt::QueuedConnection);
            QObject::connect(wrapper, SIGNAL(disable()),
                             cc, SLOT(disableObj()), Qt::QueuedConnection);
			QObject::connect(wrapper, SIGNAL(changeSectorType(int)),
							 cc, SLOT(setSecType(int)), Qt::QueuedConnection);

            m_wrappers[i][j] = wrapper;
        }
    }

	QObject::connect(uiMap, SIGNAL(focusChanged(int,int)),
					 this, SLOT(setupFocus(int,int)),  Qt::QueuedConnection);

	MonitorPanelController* monContr = MonitorPanelController::getInstance();
	QObject::connect(this, SIGNAL(updateResourceValue(int,int, int, int)),
					 monContr, SLOT(resourceChanged(int,int, int, int)));

	m_statusController = ObjectStateController::getInstance();

    qDebug() << "Connecting is done!";
}




/************************************************
 * Func: setupNewGame
 * Desc: Prepare ObjectController to new game
 ***********************************************/
void ObjectController::setupNewGame()
{
	m_buildings.clearAll();
	m_objectID = 0;

	Map* map = m_mapGenerator->generateMap();

	if(!map)
	{
		qDebug() << "ObjectController::setupNewGame: generator error!";
	}
	else
	{
		applyMapData(map);
	}

	// clear buildings

}


void ObjectController::addBuildingFactory(BuildingFactory *buildFactory, int plID)
{
	if(plID < 0 || plID >= NUMBER_OF_PLAYERS)
	{
		qDebug() << "ObjectController::addBuildingFactory: Error! wrong playerID: " << plID;
		return;
	}

	m_buildFactory[plID] = buildFactory;
}

/************************************************
 * Func: buildObj
 * Desc: Construct new object in (x,y) position
 * Return poiner if it possible
 ***********************************************/
Building* ObjectController::buildObj(OBJECT_TYPE type, int x, int y, int population, int playerID)
{
	Building* building = nullptr;

	GObjWrapper* wr = m_wrappers[x][y];
	Sector* sec = m_sectors[x][y];

	if(!sec->itApplicable())
		return nullptr;

	if(getBuilding(x, y) != nullptr)
		return nullptr;

	if(playerID < 0 || playerID >= NUMBER_OF_PLAYERS)
	{
		qDebug() << "ObjectController::buildObj: Error! wrong playerID: " << playerID;
		return nullptr;
	}

	BuildingFactory *buildFactory = m_buildFactory[playerID];

	if(buildFactory == nullptr)
	{
		qDebug() << "ObjectController::buildObj: Error! buildFactory is null for plID: " << playerID;
		return nullptr;
	}

	building = buildFactory->buildStructure(type, wr, sec, population, m_initialCounter);

	if(building != nullptr)
	{
		m_buildings.addEl(building);

		building->setID(m_objectID);
		ObjectStateController::getInstance()->addBuilding(m_objectID);
		m_objectID++;

		m_initialCounter++;
		if(m_initialCounter >= GAME_STEP_PER_SECOND)
		{
			m_initialCounter = 0;
		}
	}

	return building;
}


Building* ObjectController::updateObj(OBJECT_TYPE type, int x, int y, int playerID)
{
	Building* building = nullptr;
	Building* oldBuilding = getBuilding(x, y);

	GObjWrapper* wr = m_wrappers[x][y];
	Sector* sec = m_sectors[x][y];

	if(!sec->itApplicable())
		return nullptr;

	if(oldBuilding == nullptr)
		return nullptr;

	if(playerID < 0 || playerID >= NUMBER_OF_PLAYERS)
	{
		qDebug() << "ObjectController::updateObj: Error! wrong playerID: " << playerID;
		return nullptr;
	}

	if(playerID != oldBuilding->getPlayerID())
	{
		qDebug() << "ObjectController::updateObj: Error! new playerID: " << playerID << " but old plID: " << oldBuilding->getPlayerID();
		return nullptr;
	}

	BuildingFactory *buildFactory = m_buildFactory[playerID];

	if(buildFactory == nullptr)
	{
		qDebug() << "ObjectController::updateObj: Error! buildFactory is null for plID: " << playerID;
		return nullptr;
	}

	int population = oldBuilding->getResources(POPULATION);
	building = buildFactory->buildStructure(type, wr, sec, population, m_initialCounter);

	if(building != nullptr)
	{
		removeObject(oldBuilding, false);
		m_buildings.addEl(building);

		building->setID(m_objectID);
		ObjectStateController::getInstance()->addBuilding(m_objectID);
		m_objectID++;

		m_initialCounter++;
		if(m_initialCounter >= GAME_STEP_PER_SECOND)
		{
			m_initialCounter = 0;
		}
	}

	return building;
}

/************************************************
 * Func: removeObject(Building *building)
 * Desc: Remove object from processing. It destroy object.
 ***********************************************/
void ObjectController::removeObject(Building *building, bool deactivate)
{
	m_buildings.removeEl(building);

	if(deactivate)
	{
		building->deactivate();
	}
	building->removeWrapper();

	int plID = building->getPlayerID();
	Player* player = PlayerController::getInstance()->getPlayer(plID);

	if(player != nullptr)
	{
		player->objectWasDestroyed(building);
	}
}

/************************************************
 * Func: applyMapData(Map *map)
 * Desc: Applyes generated data to sectors
 ***********************************************/
void ObjectController::applyMapData(Map *map)
{
	for(int x = 0; x < MAP_WIDTH; x++)
	{
		for(int y = 0; y < MAP_HEIGHT; y++)
		{
			Sector* sec = m_sectors[x][y];

			OBJECT_TYPE secType = (OBJECT_TYPE)map->type.value[x][y];
			int fertility = map->fertility.value[x][y];
			int mineralWealth = map->mineralWealth.value[x][y];

			sec->setType(secType);
			sec->setFertility(fertility);
			sec->setMineralWealth(mineralWealth);

			GObjWrapper* wrapper = m_wrappers[x][y];
			wrapper->setSectorType(secType);
			wrapper->setMarker(INVALIDE_VALUE);
		}
	}
}

/************************************************
 * Func: process(int step)
 * Desc: Main process func
 ***********************************************/
void ObjectController::process(int step)
{
    //start new iteration
    m_buildings.startIter();
	int id = INVALIDE_VALUE;

    GObject* obj = m_buildings.nextEl();

    //process all buildings
    while(obj != nullptr)
    {
		id = obj->getID();
		bool isActive = !m_statusController->chackBuildingCondition(id, DESTROED_CONDITION);
		if(isActive)
		{
			obj->process(step);
		}
		else
		{
			// destroy objects and remove it from processing
			removeObject((Building*)obj);
		}

        obj = m_buildings.nextEl();
    }

	if(step == FOCUS_REFRESH_STEP)
	{
		setupFocus(m_xFocus, m_yFocus);
	}
}

/************************************************
 * Func: finalizeStep(int step)
 * Desc: complite game step
 ***********************************************/
void ObjectController::finalizeStep()
{
	//finalize iteration
	m_buildings.finilizeProc();
}

/************************************************
 * Func: getFocus(int &x, int &y)
 * Desc:return focus coordinate
 ***********************************************/
void ObjectController::getFocus(int &x, int &y)
{
	x = m_xFocus;
	y = m_yFocus;
}

/************************************************
 * Func: setupFocus(int x, int y)
 * Desc: Main process func
 ***********************************************/
void ObjectController::setupFocus(int x, int y)
{
	m_xFocus = x;
	m_yFocus = y;

	Sector* sec = m_sectors[x][y];

	int fertility = sec->getFertility();
	int mineralWealth = sec->getMineralWealth();

	emit updateResourceValue((int)FERTILITY, fertility, fertility);
	emit updateResourceValue((int)MINERAL_WEALTH, mineralWealth, mineralWealth);

	QLinkedList<iter*>* gobjList = m_buildings.getEl(x, y);

	if(gobjList->count() > 0)
	{
		highIter hiObj = gobjList->begin();
		iter* iObj = *hiObj;
		GObject* building = *(*iObj);

		RESOURSES resType = NO_RES;
		Resourse value;

		building->resetIteration();
		int numCounter = 0;

		for(; numCounter < MAX_RES_IN_ONE_SECTOR; numCounter++)
		{
			if(!building->getNextResource(resType, value))
			{
				resType = NO_RES;
				value.value = 0;
				value.type = NO_RES;
				value.maxValue = 1;
				value.displayble = true; // show empty cell
			}

			if(value.displayble)
			{
			emit updateResourceValue((int)resType, value.value, value.maxValue, numCounter);
			}
			else
			{
				// skip current resourse, it should not be displayed
				numCounter--;
			}
		}
	}
	else
	{
		for(int i = 0; i < MAX_RES_IN_ONE_SECTOR; i++)
		{
			emit updateResourceValue((int)NO_RES, 0, 0, i);
		}
	}
}



/************************************************
 * Func: getSector
 * Desc: return sector for x,y coordinate
 ***********************************************/
Sector* ObjectController::getSector(int mapX, int mapY)
{
	Sector* sec = nullptr;
	if(mapX >= 0 && mapY >= 0 && mapX < MAP_WIDTH && mapY < MAP_HEIGHT)
	{
		sec = m_sectors[mapX][mapY];
	}
	return sec;
}

/************************************************
 * Func: getBuilding
 * Desc: return building for x,y coordinate
 ***********************************************/
Building* ObjectController::getBuilding(int mapX, int mapY)
{
	Building* building = nullptr;
	if(mapX >= 0 && mapY >= 0 && mapX < MAP_WIDTH && mapY < MAP_HEIGHT)
	{
		QLinkedList<iter*>* gobjList = m_buildings.getEl(mapX, mapY);
		if(gobjList->count() > 0)
		{
			highIter hiObj = gobjList->begin();
			iter* iObj = *hiObj;
			building = static_cast<Building*>(*(*iObj));
		}
	}
	return building;
}
