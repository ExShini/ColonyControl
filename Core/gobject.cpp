#include "gobject.h"
#include "qdebug.h"
#include "gobjwrapper.h"
#include "Enums/objstatus.h"
#include "Core/playercontroller.h"

/************************************************
 * Func: GObject
 * Desc: constructor
 ***********************************************/
GObject::GObject(GObjWrapper * wrapper):
    m_wrapper(wrapper),
	m_active(true),
    m_x(0),
    m_y(0),
    m_type(INVALID_OBJ_TYPE),
	m_id(INVALIDE_VALUE),
	m_resources(),
	m_requestMap(),
	m_playerID(INVALIDE_VALUE)
{
}


/************************************************
 * Func: ~GObject
 * Desc: destructor
 ***********************************************/
GObject::~GObject()
{

}

/************************************************
 * Func: setMapCoord
 * Desc: setup map coordinates
 ***********************************************/
void GObject::setMapCoord(int x, int y)
{
    int newX = GET_REAL_X(x);
    int newY = GET_REAL_Y(y);
    setCoord(newX, newY);
}

/************************************************
 * Func: setCoord
 * Desc: setup coordinates
 ***********************************************/
void GObject::setCoord(int x, int y)
{
    m_x = x;
    m_y = y;

}

/************************************************
 * Func: setResources
 * Desc: setup current resourse's value
 ***********************************************/
int GObject::setResources(RESOURSES type, int value)
{
	int overflow = INVALIDE_VALUE;
    if(m_resources.keys().contains(type))
    {
        //we work only with natural nambers
        if(value < 0)
        {
            qDebug() << "!ERROR! GObject::setResources for type: " << type << " incorrect val: " << value;
			return overflow;
        }

        Resourse* res = m_resources[type];

		if(value > res->maxValue && res->hardLimit)
		{
			res->value = res->maxValue;
			overflow = 0;
		}
		else
		{
			res->value = value;

			if(value > res->maxValue)
				overflow = value - res->maxValue;
			else
				overflow = 0;
		}
    }

	return overflow;
}

/************************************************
 * Func: setResProgress
 * Desc: setup current resourse's progress value
 ***********************************************/
void GObject::setResProgress(RESOURSES type, int progValue)
{
	if(m_resources.keys().contains(type))
	{
		Resourse* res = m_resources[type];
		res->currentProgress = progValue;
	}
}

/************************************************
 * Func: setResLimit
 * Desc: setup resourse's limit value
 ***********************************************/
void GObject::setResLimit(RESOURSES type, int value)
{
	if(m_resources.keys().contains(type))
	{
		//we work only with natural nambers
		if(value < 0)
		{
			qDebug() << "GObject::setResLimit: ERROR! setResLimit for type: " << type << " incorrect val: " << value;
		}

		Resourse* res = m_resources[type];
		res->maxValue = value;
	}
	else
	{
		qDebug() << "GObject::setResLimit: ERROR! we have not this type: " << type;
	}
}

/************************************************
 * Func: getResources
 * Desc: return current value for resorse
 ***********************************************/
int GObject::getResources(RESOURSES type)
{
    if(m_resources.keys().contains(type))
    {
        return m_resources[type]->value;
    }

	return INVALIDE_VALUE;
}

/************************************************
 * Func: getResources
 * Desc: return current value for resorse
 ***********************************************/
Resourse* GObject::getResourcesObj(RESOURSES type)
{
	if(m_resources.keys().contains(type))
	{
		return m_resources[type];
	}

	return nullptr;
}

/************************************************
 * Func: getResLimit
 * Desc: return current limit value for resorse
 ***********************************************/
int GObject::getResLimit(RESOURSES type)
{
	if(m_resources.keys().contains(type))
	{
		return m_resources[type]->maxValue;
	}

	return INVALIDE_VALUE;
}

/************************************************
 * Func: regResourse
 * Desc: registr new resourse for current GObject
 * Note: This routine used only for Units! For Building we should use smurt version of regResourse(RESOURSES type) call
 ***********************************************/
void GObject::regResourse(RESOURSES type, int maxValue, int defValue, bool hard)
{
    if(!m_resources.keys().contains(type))
    {
        Resourse* res = new Resourse();
        res->type = type;
        res->maxValue = maxValue;
        res->value = defValue;
		res->hardLimit = hard;
        m_resources[type] = res;

		m_requestMap[type] = nullptr;
    }
    else
    {
        qDebug() << "!ERROR! GObject::regResourse double registration of type: " << type;
    }
}


/************************************************
 * Func: regResourse
 * Desc: registr new resourse for current GObject
 ***********************************************/
void GObject::regResourse(RESOURSES type)
{
	if(!m_resources.keys().contains(type))
	{
		Player* player = PlayerController::getInstance()->getPlayer(m_playerID);

		Resourse* proto = player->getResPrototype(m_type, type, 0);
		Resourse* res = new Resourse(proto);
		res->value = player->getResDefaultValue(m_type, type);

		/* INFROSTRUCTURE have some specific in handling - we need to know low and top limits
		** current level limit determine low limit
		** next level limit determine top limit
		*/
		if(type == INFROSTRUCTURE)
		{
			res->maxValue = player->getResLimit(m_type, INFROSTRUCTURE, 1);
		}

		m_resources[type] = res;
		m_requestMap[type] = nullptr;
	}
	else
	{
		qDebug() << "!ERROR! GObject::regResourse double registration of type: " << type;
	}
}

/************************************************
 * Func: updateResourse
 * Desc: update resourse settings for current GObject from prototype object
 ***********************************************/
void GObject::updateResourse(RESOURSES type, int level, bool initial)
{
	if(m_resources.keys().contains(type))
	{
		Player* player = PlayerController::getInstance()->getPlayer(m_playerID);

		/* INFROSTRUCTURE have some specific in handling - we need to know low and top limits
		** current level limit determine low limit
		** next level limit determine top limit
		*/
		if(type == INFROSTRUCTURE)
		{
			level++;
		}


		Resourse* proto = player->getResPrototype(m_type, type, level);
		Resourse* res = m_resources[type];
		int currValue = res->value;
		int currProgress = res->currentProgress;

		// copy settings from prototype to current res object
		memcpy(res, proto, sizeof(Resourse));

		// restore current valuea and progress of resource
		res->value = currValue;
		res->currentProgress = currProgress;

		if(initial)
		{
			res->value = player->getResDefaultValue(m_type, type);
		}
	}
	else
	{
		qDebug() << "!ERROR! GObject::updateResourse we have not such res of type: " << type;
	}
}

/************************************************
 * Func: requestComplited
 * Desc: complite request for current GObject
 ***********************************************/
void GObject::requestComplited(RESOURSES resType)
{
	if(m_requestMap.keys().contains(resType))
	{
		m_requestMap[resType] = nullptr;
	}
	else
	{
		qDebug() << "!ERROR! GObject::requestComplited incorrect resType: " << resType;
	}
}

/************************************************
 * Func: resetIteration
 * Desc: reset resourse enumeration
 ***********************************************/
void GObject::resetIteration()
{
	m_curResource = m_resources.begin();
}

/************************************************
 * Func: getNextResource
 * Desc: provide next resourse
 ***********************************************/
bool GObject::getNextResource(RESOURSES &type, Resourse &value)
{
	bool state = true;

	if(m_curResource == m_resources.end())
	{
		state = false;
		return state;
	}

	type = m_curResource.key();
	memcpy(&value, m_curResource.value(), sizeof(Resourse));
	m_curResource++;

	return state;
}

/************************************************
 * Func: deactivate
 * Desc: deactivate GObject. Should be called befor destroying
 ***********************************************/
void GObject::deactivate()
{
	if(m_wrapper != nullptr)
	{
		m_wrapper->setDisabled();
		m_wrapper->setLevel(0, UI_NORMAL);
		m_wrapper->setType(INVALID_OBJ_TYPE);
	}

	QMap<RESOURSES, Request*>::iterator iter = m_requestMap.begin();
	QMap<RESOURSES, Request*>::iterator end = m_requestMap.end();

	for(; iter != end; iter++)
	{
		Request* req = iter.value();
		if(req != nullptr)
		{
			req->status = NOT_ACTUAL;
		}
	}
}


/************************************************
 * Func: addRequst
 * Desc: add new request to m_requestMap
 ***********************************************/
void GObject::addRequst(Request *req)
{
	if(req != nullptr)
	{
		RESOURSES resType = req->resType;

		if(m_requestMap.keys().contains(resType))
		{
			m_requestMap[resType] = req;
		}
	}
}

void GObject::takeDamage(int damage)
{
	// should be implemented in subclasses
	Q_UNUSED(damage);
}
