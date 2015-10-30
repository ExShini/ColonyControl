#include "uidrawer.h"
#include "UIElements/uiresdictionary.h"
#include "AudioModule/audiocontroller.h"

#include "QDebug"

/************************************************
 * Func: UIDrawer(int argc, char *argv[])
 * Desc: Constructor.
 ***********************************************/
UIDrawer::UIDrawer(int argc, char *argv[])
{

	m_app = new QApplication(argc, argv);
    m_engine = new QQmlApplicationEngine();

	AudioController::getInstance()->setEngine(m_engine);

    m_timerManager = UITimingManager::getInstance();
    m_timerManager->start();

    m_mapController = UIMapController::getInstance();
    m_mapController->setEngine(m_engine);

    m_menuController = MenuController::getInstance();
    m_menuController->setEngine(m_engine);

	m_monitorController = MonitorPanelController::getInstance();
	m_monitorController->setEngine(m_engine);

	m_uiUnitController = UiUnitController::getInstance();
	m_uiUnitController->setEngine(m_engine);

	m_abilityMenuCntr = AbilityMenuController::getInstance();
	m_abilityMenuCntr->setEngine(m_engine);

    UIResDictionary::getInstance();


	//connect internal components
	QObject::connect(m_menuController, SIGNAL(gameIsStarted()),
					 m_mapController, SLOT(startGame()), Qt::QueuedConnection);

	QObject::connect(m_menuController, SIGNAL(gameIsStarted()),
					 m_monitorController, SLOT(showElent()), Qt::QueuedConnection);

}

/************************************************
 * Func: init()
 * Desc: Initialize UIDrawer's components.
 ***********************************************/
void UIDrawer::init()
{
	m_mapController->registerComponent();
	m_uiUnitController->registerComponent();
	m_abilityMenuCntr->registerComponent();

	m_monitorController->init();
    m_menuController->init();
	m_monitorController->init();

	loadGUI();	// load qml main file here

	m_mapController->init();	// should be after loadGUI by the reason that mapController create cellCntrs
	m_uiUnitController->init();
	m_abilityMenuCntr->init();
}

/************************************************
 * Func: loadGUI()
 * Desc: load main.qml file and start drawing
 ***********************************************/
void UIDrawer::loadGUI()
{
	m_engine->load(QUrl(QStringLiteral("qrc:/res/main.qml")));
}

/************************************************
 * Func: exec()
 * Desc: Start UI drawing.
 ***********************************************/
void UIDrawer::exec()
{
    qDebug()<< "StardDrawing!";
    m_app->exec();
}
