#include "playercontroller.h"
#include "player/Human/humanplayer.h"
#include "player/Aroi/aroiplayer.h"
#include "UIDrawer/UIElements/uiresdictionary.h"
#include "UIDrawer/UIElements/monitorpanelcontroller.h"
#include "UIDrawer/UIElements/abilitymenucontroller.h"
#include "objectcontroller.h"
#include "qdebug.h"

PlayerController* PlayerController::s_instance = nullptr;

/************************************************
 * Func: PlayerController
 * Desc: constructor
 ***********************************************/
PlayerController::PlayerController(QObject *parent):
	QObject(parent),
	m_initPlID(0)
{
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		m_players[i] = nullptr;
	}
}

/************************************************
 * Func: ~PlayerController
 * Desc: destructor
 ***********************************************/
PlayerController::~PlayerController()
{

}

/************************************************
 * Func: setupNewGame
 * Desc: Prepare PlayerController to new game
 ***********************************************/
void PlayerController::setupNewGame()
{
	resetPlayerObjects();
}

/************************************************
 * Func: resetPlayerObjects
 * Desc: reset all players to null (clear memory if it needed)
 ***********************************************/
void PlayerController::resetPlayerObjects()
{
	m_initPlID = 0;
	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		Player* player = m_players[i];
		if(player != nullptr)
		{
			delete player;
		}
	}
}

/************************************************
 * Func: init
 * Desc: initialization of PlayerController's stuff
 ***********************************************/
void PlayerController::init()
{
	QObject::connect(this, SIGNAL(updatePlayerRes(int,int,int,int)),
					 MonitorPanelController::getInstance(), SLOT(resourceChanged(int,int,int,int)), Qt::QueuedConnection);

	QObject::connect(this, SIGNAL(abilityIsActived(int,int)),
					 AbilityMenuController::getInstance(), SLOT(abilityActived(int,int)), Qt::QueuedConnection);

	QObject::connect(AbilityMenuController::getInstance(), SIGNAL(resetAbility(int)),
					 this, SLOT(resetPlayerAbility(int)), Qt::QueuedConnection);

	QObject::connect(AbilityMenuController::getInstance(), SIGNAL(tryApplyAbility(int, int, int)),
					 this, SLOT(applyPlayerAbility(int, int, int)), Qt::QueuedConnection);
}

/************************************************
 * Func: addPlayer
 * Desc: add new player to game
 ***********************************************/
void PlayerController::addPlayer(Race race)
{
	if(m_initPlID >= NUMBER_OF_PLAYERS)
	{
		qDebug() << "PlayerController::addPlayer: ERROR! m_initPlID already max";
		return;
	}

	Player* player = nullptr;

	switch (race) {
	case Human:
	{
		player = new HumanPlayer(m_initPlID);
		player->init();
	}
		break;
	case Aroi:
	{
		player = new AroiPlayer(m_initPlID);
		player->init();
	}
		break;
	default:
		break;
	}


	if(player == nullptr)
	{
		qDebug() << "PlayerController::addPlayer : player is null, creation error!";
		return;
	}

	m_players[m_initPlID] = player;
	UIResDictionary::getInstance()->registerPlayer(race, m_initPlID);

	if(m_initPlID < NUMBER_OF_PLAYERS - 1)
	{
		m_initPlID++;
	}
}


/************************************************
 * Func: getInstance
 * Desc: singliton implementation
 ***********************************************/
PlayerController* PlayerController::getInstance()
{
	if(s_instance == nullptr)
	{
		s_instance = new PlayerController();
	}

	return s_instance;
}

/************************************************
 * Func: getPlayer
 * Desc: return player object by id
 ***********************************************/
Player* PlayerController::getPlayer(int playerID)
{
	Player* player = nullptr;

	if(playerID >= 0 && playerID < NUMBER_OF_PLAYERS)
	{
		player = m_players[playerID];

		if(player == nullptr)
		{
			qDebug() << "PlayerController::getPlayer : ERROR! unregistred player is requared! Pl id: " << playerID;
		}
	}
	else
	{
		qDebug() << "PlayerController::getPlayer : ERROR! incorrect player id : " << playerID;
	}

	return player;
}

/************************************************
 * Func: process
 * Desc: process player's and AI's parameters
 ***********************************************/
void PlayerController::process(int step)
{
	if(step == 0)
	{
		int mainResVal = m_players[MAIN_PLAYER_ID]->getMainResValue();
		emit updatePlayerRes((int)MAIN_RESOURSE, mainResVal, 0, MAIN_RACE_RES_POSITION);

		// refrash abilities for all active players
		for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
		{
			Player* player = m_players[i];
			if(player != nullptr)
			{
				player->refreshAbility();
			}
		}
	}
}

/************************************************
 * Func: activateAbility
 * Desc: switch ability to active state
 ***********************************************/
void PlayerController::activateAbility(int type, int subType, int playerID)
{
	Player * player = getPlayer(playerID);

	qDebug() << "PlayerController::activateAbility for type " << type << " subType " << subType << " playerID " << playerID;

	if(player == nullptr)
	{
		qDebug() << "PlayerController::activateAbility: Error! Player not avalibale for plID: " << playerID;
		return;
	}

	if(player->activeAbility(type, subType))
	{
		emit abilityIsActived(type, subType);
	}
	else
	{
		qDebug() << "PlayerController::activateAbility: Error! Can not apply ability type: " << type
				 << " subType: " << subType <<" for player: " << playerID;
	}
}

/************************************************
 * Func: resetPlayerAbility
 * Desc: reset ability for player with playerID
 ***********************************************/
void PlayerController::resetPlayerAbility(int playerID)
{
	Player * player = getPlayer(playerID);

	if(player == nullptr)
	{
		qDebug() << "PlayerController::resetPlayerAbility: Error! Player not avalibale for plID: " << playerID;
		return;
	}

	player->resetAbility();
}

/************************************************
 * Func: applyPlayerAbility
 * Desc: apply active ability to x,y sector
 ***********************************************/
void PlayerController::applyPlayerAbility( int x, int y, int playerID)
{
	Player * player = getPlayer(playerID);

	if(player == nullptr)
	{
		qDebug() << "PlayerController::applyPlayerAbility: Error! Player not avalibale for plID: " << playerID;
		return;
	}

	player->applyAbilityAt(x, y);

	// reset mouse marker
	emit abilityIsActived(INVALIDE_TYPE, INVALIDE_VALUE);
}
