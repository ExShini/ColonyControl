#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H
#include "Enums/guisettings.h"
#include "Enums/gameprocessingsettings.h"
#include "Core/smcont.h"
#include "Units/unit.h"
#include "Units/unitfactory.h"

#include "qlist.h"
#include "QObject"

class ObjectStateController;
class Building;

class UnitController: public QObject
{
	Q_OBJECT
public:

	static UnitController* getInstance();
	void init();

	void process(int step);
	void finalizeStep();

	Unit* buildUnit(Building* base, OBJECT_TYPE unitType);
	Unit* buildAbilityExecutor(int playerID, OBJECT_TYPE unitType);
	void addUnitFactory(UnitFactory* factory, int playerID);
	void returnUnitWrapper(UnitWrapper* wrapper);

public slots:
	void setupNewGame();

protected:
	UnitController(QObject* parent = nullptr);
	~UnitController();

	static UnitController* s_instance;

	UnitWrapper* m_wrappers[MAX_NUMBER_OF_UNITS];
	SmCont m_units;

	QList<UnitWrapper*> m_freeWrappers;
	QList<UnitWrapper*> m_inUseWrappers;
	UnitFactory* m_unitFactories[NUMBER_OF_PLAYERS];
	ObjectStateController* m_statusController;

	int m_unitID;
};

#endif // UNITCONTROLLER_H
