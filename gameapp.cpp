#include "gameapp.h"

/************************************************
 * Func: GameApp
 * Desc: Constructor.
 * Root class of game.
 ***********************************************/
GameApp::GameApp(int argc, char *argv[])
{
	m_core = new GameCore();
	m_drawer = new UIDrawer(argc, argv);
	m_audioController = AudioController::getInstance();
}

/************************************************
 * Func: init
 * Desc: Initialize game modules
 ***********************************************/
void GameApp::init()
{
	m_core->init();
	m_audioController->init();
	m_drawer->init();

	connectUIandCore();
}

/************************************************
 * Func: start
 * Desc: start game!
 ***********************************************/
void GameApp::start()
{
	m_drawer->exec();
}

/************************************************
 * Func: connectUIandCore
 * Desc: connect UI and Core modules
 ***********************************************/
void GameApp::connectUIandCore()
{
	MenuController* menuCtr = MenuController::getInstance();
	QObject::connect(menuCtr, SIGNAL(gameIsStarted()),
					 m_core, SLOT(startGame()), Qt::QueuedConnection);
}
