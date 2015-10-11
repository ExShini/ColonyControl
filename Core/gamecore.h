#ifndef GAMECORE_H
#define GAMECORE_H
#include "QObject"
#include "QThread"
#include "QTimer"

#include "objectcontroller.h"
#include "playercontroller.h"
#include "UnitController/unitcontroller.h"

class GameCore: public QObject
{
    Q_OBJECT
public:
    GameCore(QObject* parent = nullptr);
    void init();


public slots:
    void startGame();

signals:
    void startNewGame();

private:
    void initGameObject();


    QThread* m_coreThread;
    QTimer * m_mainTaimer;

    int m_currentGStep;

    ObjectController* m_objController;
	PlayerController* m_playerController;
	UnitController * m_unitController;

private slots:
    void mainGameLoop();


};

#endif // GAMECORE_H
