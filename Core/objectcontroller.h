#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H
#include "QObject"
#include "gobject.h"

#include "Enums/gameprocessingsettings.h"
#include "Enums/mapsettings.h"
#include "smcont.h"
#include "mapgenerator.h"
#include "buildings/buildingfactory.h"
#include "objectstatecontroller.h"

#define FOCUS_REFRESH_STEP 1

class GObjWrapper;
class Sector;
class Building;

class ObjectController: public QObject
{
    Q_OBJECT
public:

    static ObjectController* getInstance();
    void init();

    void process(int step);
	void finalizeStep();

	Building* buildObj(OBJECT_TYPE type, int x, int y, int population, int playerID);
	Building* updateObj(OBJECT_TYPE type, int x, int y, int playerID);
	Sector* getSector(int mapX, int mapY);
	Building* getBuilding(int mapX, int mapY);

	void addBuildingFactory(BuildingFactory* buildFactory, int plID);
	void getFocus(int & x, int & y);

public slots:
    void setupNewGame();
	void setupFocus(int x, int y);

signals:
	void updateResourceValue(int type, int value, int maxValue, int number = -1);

protected:
    static ObjectController* s_instance;

    ObjectController(QObject * parent = 0);
    ~ObjectController();

	void applyMapData(Map* map);
	void removeObject(Building *building, bool deactivate = true);

    GObjWrapper* m_wrappers[MAP_WIDTH][MAP_HEIGHT];
	Sector* m_sectors[MAP_WIDTH][MAP_HEIGHT];
    SmCont m_buildings;
	MapGenerator * m_mapGenerator;
	BuildingFactory* m_buildFactory[NUMBER_OF_PLAYERS];
	ObjectStateController* m_statusController;


	int m_xFocus, m_yFocus;
	int m_initialCounter;
	int m_objectID;

};

#endif // OBJECTCONTROLLER_H
