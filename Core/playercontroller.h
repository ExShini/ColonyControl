#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "qobject.h"
#include "player/player.h"
#include "Enums/gameprocessingsettings.h"

class PlayerController: public QObject
{
	Q_OBJECT
public:
	static PlayerController* getInstance();
	void init();
	Player* getPlayer(int playerID);
	void addPlayer(Race race);

	void process(int step);

signals:
	void updatePlayerRes(int type, int value, int maxValue, int number);
	void abilityIsActived(int type, int subType);

public slots:
	void setupNewGame();
	void activateAbility(int type, int subType, int playerID);
	void resetPlayerAbility(int playerID);
	void applyPlayerAbility(int x, int y, int playerID);

protected:
	PlayerController(QObject* parent = nullptr);
	~PlayerController();


	void resetPlayerObjects();

	int m_initPlID;
	static PlayerController* s_instance;
	Player* m_players[NUMBER_OF_PLAYERS];


};

#endif // PLAYERCONTROLLER_H
