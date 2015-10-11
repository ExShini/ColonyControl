#ifndef GAMEAPP_H
#define GAMEAPP_H
#include "QObject"
#include "UIDrawer/uidrawer.h"
#include "Core/gamecore.h"
#include "AudioModule/audiocontroller.h"

class GameApp: public QObject
{
    Q_OBJECT
public:
    GameApp(int argc, char *argv[]);

    void init();
    void start();

private:
    void connectUIandCore();

    UIDrawer* m_drawer;
    GameCore* m_core;
	AudioController* m_audioController;
};

#endif // GAMEAPP_H
