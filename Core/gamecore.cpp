#include "gamecore.h"
#include "objectcontroller.h"
#include "playercontroller.h"
#include "UnitController/unitcontroller.h"
#include "Enums/coresettings.h"
#include "randomgen.h"
#include "qdebug.h"


/************************************************
 * Func: GameCore(QObject *parent)
 * Desc: Constructor.
 ***********************************************/
GameCore::GameCore(QObject *parent):
    QObject(parent),
    m_currentGStep(0)
{
    m_coreThread = new QThread();
    this->moveToThread(m_coreThread);

    m_mainTaimer = new QTimer();
    m_mainTaimer->setInterval(ONE_SECOND / GAME_STEP_PER_SECOND);

    m_mainTaimer->moveToThread(m_coreThread);

    m_objController = ObjectController::getInstance();
    m_objController->moveToThread(m_coreThread);

	m_playerController = PlayerController::getInstance();
	m_playerController->moveToThread(m_coreThread);

	m_unitController = UnitController::getInstance();
	m_unitController->moveToThread(m_coreThread);

    QObject::connect(m_mainTaimer, SIGNAL(timeout()),
                     this, SLOT(mainGameLoop()));

    //start timer at one moment with thread
    QObject::connect(this, SIGNAL(startNewGame()),
                     m_mainTaimer, SLOT(start()));

	QObject::connect(this, SIGNAL(startNewGame()),
					 m_playerController, SLOT(setupNewGame()));

    QObject::connect(this, SIGNAL(startNewGame()),
                     m_objController, SLOT(setupNewGame()));

	QObject::connect(this, SIGNAL(startNewGame()),
					 m_unitController, SLOT(setupNewGame()));

}


/************************************************
 * Func: startGame()
 * Desc: Start new game
 ***********************************************/
void GameCore::startGame()
{
    qDebug() << "GameCore::startGame";
    m_currentGStep = 0;
    emit startNewGame();

	initGameObject();
}


/************************************************
 * Func: initGameObject()
 * Desc: Initialize game objects by default value. Should
 * be invoked each time than we want to start (restart) new game.
 ***********************************************/
void GameCore::initGameObject()
{
	// create objects for first game step

	m_playerController->addPlayer(Human);
	m_playerController->addPlayer(Aroi);

//	for(int i = 2; i < 5; i ++)
//	{
//		for(int j = 2; j < 5; j++)
//		{
//			if(m_objController->buildObj(t_HUMAN_COLONY_CENTER, i, j, 1000, 0) != nullptr)
//			{
//				j = 16;
//				i = 16;
//			}
//		}
//	}


	for(int i = 12; i < 17; i ++)
	{
		for(int j = 12; j < 17; j++)
		{
			if(m_objController->buildObj(t_AROI_HIVE, i, j, 100, 1) != nullptr)
			{
				j = 16;
				i = 16;
			}
		}
	}
}

/************************************************
 * Func: init()
 * Desc: Initialize entry GameCore components and mechanisms.
 ***********************************************/
void GameCore::init()
{
	RandomGen::init();
	m_playerController->init();
	m_unitController->init();
    m_objController->init();

    //if game thread not started - change it. Game must go on :)
    if(!m_coreThread->isRunning())
    {
        m_coreThread->start();
    }
}

/************************************************
 * Func: mainGameLoop()
 * Desc: Main game functions.
 ***********************************************/
void GameCore::mainGameLoop()
{
    m_objController->process(m_currentGStep);
	m_unitController->process(m_currentGStep);
	m_playerController->process(m_currentGStep);


	m_objController->finalizeStep();
	m_unitController->finalizeStep();

    //increase game step
    m_currentGStep++;
    if(m_currentGStep >= GAME_STEP_PER_SECOND)
    {
        // reset counter if it achieve GAME_STEP_PER_SECOND value
        m_currentGStep = 0;
    }
}
