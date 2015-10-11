#include "player.h"
#include "qdebug.h"
#include "Core/objectcontroller.h"
#include "UIDrawer/UIElements/abilitymenucontroller.h"

Player::Player(int id, Race race):
	m_ID(id),
	m_builManager(nullptr),
	m_abilityManager(nullptr),
	m_mainResource(5000),
	m_race(race),
	m_abilityType(INVALIDE_TYPE),
	m_abilitySubType(INVALIDE_VALUE)
{
	m_reqManager = new RequestManager();
}

Player::~Player()
{
	delete m_reqManager;
}

void Player::init()
{

	// clear limit table
	for(int type = t_FIRST_OBJ; type < NUM_OF_OBJ_TYPES; type++)
	{
		for(int res = FIRST_RES; res <= LAST_PARAMETER; res++)
		{
			for(int level = 0; level < MAX_LEVEL; level++)
			{
				m_buildingLimits[type][res][level] = INVALIDE_VALUE;
			}
		}
	}

    //m_prototypes
    // clear prototype table
    for(int type = t_FIRST_OBJ; type < NUM_OF_OBJ_TYPES; type++)
    {
        for(int res = FIRST_RES; res <= LAST_PARAMETER; res++)
        {
            ResPrototype* prot = new ResPrototype();
            prot->defValue = INVALIDE_VALUE;
            m_prototypes[type][res] = prot;
            for(int level = 0; level < MAX_LEVEL; level++)
            {
                prot->resorses[level] = nullptr;
            }
        }
    }
}

void Player::setResLimit(OBJECT_TYPE type, RESOURSES res, int level, int value)
{
	m_buildingLimits[type][res][level] = value;
}

void Player::setResToPrototype(OBJECT_TYPE type, Resourse *res, int level)
{
    if(res == nullptr)
    {
        qDebug() << "Player::setResPrototype: Error! res is null.";
        return;
    }

    if(type < 0 || type >= NUM_OF_OBJ_TYPES)
    {
        qDebug() << "Player::setResPrototype: Error! type is wrong! type: " << type;
        return;
    }

    if(level < 0 || level > MAX_LEVEL)
    {
        qDebug() << "Player::setResPrototype: Error! level is wrong! level: " << level;
        return;
    }

    RESOURSES resType = res->type;
    m_prototypes[type][resType]->resorses[level] = res;
}

void Player::setDefValue(OBJECT_TYPE type, RESOURSES resType, int defValue)
{
    m_prototypes[type][resType]->defValue = defValue;
}

int Player::getResLimit(OBJECT_TYPE buildingType, RESOURSES res, int level)
{
	int val = m_buildingLimits[buildingType][res][level];

	if(val == INVALIDE_VALUE)
	{
		qDebug() << "Player::getResLimit : Error!!! incorrect limit settings for objType:" << buildingType <<
					" res:" << res << " level:" << level;
	}

	return val;
}

void Player::addRequest(Request *request)
{
	m_reqManager->addRequest(request);
}

Request* Player::getRequest(RESOURSES resType, REQ_TYPE reqType, int mapX, int mapY)
{
	Request* req = nullptr;
	bool tryFindRequest = true;

	while(tryFindRequest)
	{
		req = m_reqManager->findRequest(resType, reqType, mapX, mapY);

		if(req == nullptr)
		{
			tryFindRequest = false;
		}
		else if(req->status != NOT_ACTUAL)
		{
			tryFindRequest = false;
		}
		else
		{
			// delete NOT_ACTUAL request and try to find actual
			delete req;
		}

	}

	return req;
}

bool Player::activeAbility(int type, int subType)
{
	bool success = false;

	if(type == UPDATE_BUILDING)
	{
		int cost = m_builManager->getCostOf((OBJECT_TYPE)subType);
		if(cost <= m_mainResource && cost!= INVALIDE_VALUE)
		{
			success = true;

			m_abilityType = (ABILITY_TYPE)type;
			m_abilitySubType = subType;
		}
		else
		{
			m_abilityType = INVALIDE_TYPE;
			m_abilitySubType = INVALIDE_VALUE;

			qDebug() << "Player::activateAbility: Warning! not enough res. Type: " << type << " playerId: " << m_ID << " race: " << m_race;
		}
	}
	else if(type == ABILITY)
	{
		int cost = m_abilityManager->getCostOf((ABILITIES)subType);
		if(cost <= m_mainResource && cost!= INVALIDE_VALUE)
		{
			success = true;

			m_abilityType = (ABILITY_TYPE)type;
			m_abilitySubType = subType;
		}
	}
	else
	{
		m_abilityType = INVALIDE_TYPE;
		m_abilitySubType = INVALIDE_VALUE;
		qDebug() << "Player::activateAbility: Warning! wrong type: " << type << " playerId: " << m_ID << " race: " << m_race;
	}

	return success;
}

void Player::resetAbility()
{
	m_abilityType = INVALIDE_TYPE;
	m_abilitySubType = INVALIDE_VALUE;
}

bool Player::applyAbilityAt(int x, int y)
{
	bool succes = false;

	if(m_abilityType == INVALIDE_TYPE || m_abilitySubType == INVALIDE_VALUE)
	{
		qDebug() << "Player::applyAbilityAt: empty ability";
		return false;
	}

	if(m_abilityType == UPDATE_BUILDING)
	{
		OBJECT_TYPE type = (OBJECT_TYPE)m_abilitySubType;
		int cost = m_builManager->getCostOf(type);

		Building* building = ObjectController::getInstance()->updateObj(type, x, y, m_ID);
		if(building != nullptr)
		{
			int newCost = m_builManager->objectWasBuilded(type);

			if(m_ID == MAIN_PLAYER_ID)
			{
				AbilityMenuController::getInstance()->setAbilityCost(m_abilityType, m_abilitySubType, newCost);
			}

			m_mainResource -= cost;
			m_abilityType = INVALIDE_TYPE;
			m_abilitySubType = INVALIDE_VALUE;
			succes = true;
		}
	}
	else if(m_abilityType == ABILITY)
	{
		// TODO
		Building* building = ObjectController::getInstance()->getBuilding(x, y);

		if(building != nullptr)
		{
			int cost = m_abilityManager->getCostOf((ABILITIES)m_abilitySubType);
			int newCost = m_abilityManager->abilityWasApplied((ABILITIES)m_abilitySubType, building);

			if(m_ID == MAIN_PLAYER_ID)
			{
				AbilityMenuController::getInstance()->setAbilityCost(m_abilityType, m_abilitySubType, newCost);
			}
			m_mainResource -= cost;

			m_abilityType = INVALIDE_TYPE;
			m_abilitySubType = INVALIDE_VALUE;
			succes = true;
		}
	}
	else
	{
		qDebug() << "Player::applyAbilityAt: Error! Unknown type : " << m_abilityType;
		return false;
	}


	return succes;
}

void Player::objectWasDestroyed(Building* building)
{
	if(building != nullptr)
	{
		OBJECT_TYPE type = building->getType();
		int newCost = m_builManager->objectWasDestroed(type);

		if(m_ID == MAIN_PLAYER_ID)
		{
			// try update cost for building ability
			AbilityMenuController::getInstance()->setAbilityCost(UPDATE_BUILDING, type, newCost);
		}
	}
	else
	{
		qDebug() << "Player::objectWasDestroyed: Error! building is null!";
	}
}

void Player::refreshAbility()
{
	if(m_abilityManager != nullptr)
	{
		m_abilityManager->refreshAbilities();
	}
}
