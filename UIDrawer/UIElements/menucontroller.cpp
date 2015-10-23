#include "menucontroller.h"
#include "Enums/colonycontrol.h"
#include "QDebug"

MenuController* MenuController::s_instance = nullptr;

/************************************************
 * Func: MenuController(QObject *parent)
 * Desc: Constructor
 ***********************************************/
MenuController::MenuController(QObject *parent):
    QObject(parent)
{

}

/************************************************
 * Func: ~MenuController
 * Desc: Destructor
 ***********************************************/
MenuController::~MenuController()
{

}

/************************************************
 * Func: getInstance()
 * Desc: Singleton implementation
 ***********************************************/
MenuController * MenuController::getInstance()
{
	if(s_instance == nullptr)
    {
		s_instance = new MenuController();
    }

	return s_instance;
}

/************************************************
 * Func: setEngine(QQmlApplicationEngine *engine)
 * Desc: Set engine to UIMapController
 ***********************************************/
void MenuController::setEngine(QQmlApplicationEngine *engine)
{
    m_engine = engine;
}


/************************************************
 * Func: init()
 * Desc: Initialize all MenuController's components and mechanism
 ***********************************************/
void MenuController::init()
{
    //if engine is null - ERROR!
    if(m_engine == nullptr)
    {
        qDebug() << "UIMapController::init: Engine doesn't set!";
        return;
    }

    m_engine->rootContext()->setContextProperty("MenuController", this);
}

/************************************************
 * Func: startGame()
 * Desc: This function invoked from QML and emit gameIsStarted signal.
 * This signal should start game processing in core components.
 ***********************************************/
void MenuController::startGame()
{
    qDebug() << "MenuController::startGame()";
    emit gameIsStarted();
}

QString MenuController::getCCVersion()
{
    QString major = QString::number(VERSION_MAJOR);
    QString minor = QString::number(VERSION_MINOR);
    return "V." + major + "." + minor;
}
