#ifndef ABILITYMENUCONTROLLER_H
#define ABILITYMENUCONTROLLER_H

#include "qqmlcomponent.h"
#include "qquickitem.h"
#include <QQmlApplicationEngine>
#include <QObject>
#include <QMap>

#include "abilitybuttoncntr.h"
#include "Enums/guisettings.h"
#include "markercontroller.h"
#include "Enums/gameprocessingsettings.h"

#define GET_ABILITY_KEY(type,subType) ((type << 8) + subType)

class AbilityMenuController : public QObject
{
	Q_OBJECT
public:

	Q_INVOKABLE AbilityButtonCntr* getAbilityCntr();
	Q_INVOKABLE void sectorChoosed();
	Q_INVOKABLE void resetMarker();

	void setEngine(QQmlApplicationEngine* engine);
	static AbilityMenuController* getInstance();
	void init();
	void registerComponent();

	void setAbilityCost(ABILITY_TYPE type, int subType, int cost);
	int addAbility(ABILITY_TYPE type, int subType, int defCost, AbilityButtonCntr::ABILITY_STATE state);

signals:
	void resetAbility(int plID = MAIN_PLAYER_ID);
	void tryApplyAbility(int x, int y, int plID = MAIN_PLAYER_ID);

public slots:
	void abilityActived(int type, int subType);

protected:
	explicit AbilityMenuController(QObject *parent = 0);


	static AbilityMenuController* s_instance;
	QQmlApplicationEngine* m_engine;
	AbilityButtonCntr* m_abilityButtons[MAX_NUMBER_OF_ABILITY_BUTTONS];
	QQmlComponent* m_abilityCreator;
	QQuickItem* m_buildPanel;

	int m_abilityCnt;
	MarkerController* m_markerCntr;
	QMap<int, AbilityButtonCntr*> m_registredAbility;
};

#endif // ABILITYMENUCONTROLLER_H
