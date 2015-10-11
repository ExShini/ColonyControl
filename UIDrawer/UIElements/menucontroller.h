#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include "qqmlcomponent.h"
#include <QQmlApplicationEngine>
#include "qqmlcontext.h"

class MenuController : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void startGame();

    static MenuController* getInstance();


    void init();
    void setEngine(QQmlApplicationEngine *engine);



signals:
    void gameIsStarted();

public slots:

private:
    static MenuController* s_instance;

    explicit MenuController(QObject *parent = 0);
    ~MenuController();

    QQmlApplicationEngine * m_engine;
};

#endif // MENUCONTROLLER_H
