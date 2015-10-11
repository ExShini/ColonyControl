#ifndef UIDRAWER_H
#define UIDRAWER_H

#include <QApplication>
#include "UIElements/uimapcontroller.h"
#include "UIElements/menucontroller.h"
#include "UIElements/monitorpanelcontroller.h"
#include "UIElements/uiunitcontroller.h"
#include "UIElements/abilitymenucontroller.h"




class UIDrawer
{
public:
    UIDrawer(int argc, char *argv[]);

    void init();
    void exec();


private:
	void loadGUI();

    QApplication* m_app;
    QQmlApplicationEngine* m_engine;

    UIMapController* m_mapController;
    MenuController * m_menuController;
	MonitorPanelController* m_monitorController;
	UiUnitController* m_uiUnitController;
	AbilityMenuController* m_abilityMenuCntr;

};

#endif // UIDRAWER_H
