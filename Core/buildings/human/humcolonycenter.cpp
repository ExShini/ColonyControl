#include "humcolonycenter.h"
#include "Core/gobjwrapper.h"
#include "Core/UnitController/unitcontroller.h"
#include "qdebug.h"

HumColonyCenter::HumColonyCenter(GObjWrapper *wrapper, Sector *sector, int population, int initialStep, int plID):
	HumSettlers(wrapper, sector, population, initialStep, plID),
	m_pionersInBase(),
	m_pioners()
{
	m_type = t_HUMAN_COLONY_CENTER;

	m_wrapper->setType(m_type);
	m_wrapper->setLevel(0);
	m_wrapper->setEnabled();


	updateResourse(POPULATION, m_level);
	updateResourse(SUPPLY, m_level);
	updateResourse(INFROSTRUCTURE, m_level);

	//	setResLimit(POPULATION, m_player->getResLimit(m_type, POPULATION, m_level));
	//	setResLimit(SUPPLY, m_player->getResLimit(m_type, SUPPLY, m_level));
	//	setResLimit(INFROSTRUCTURE, m_player->getResLimit(m_type, INFROSTRUCTURE, m_level + 1));

	regResourse(SHIPS);


	m_maxLevel = HUMAN_MAX_COLONY_CENTER_LEVEL;


	radar = new EmptySectorRadar(getMapX(), getMapY(), m_playerID);
	radar->setSetting(5, 3);
}

HumColonyCenter::~HumColonyCenter()
{

}

void HumColonyCenter::process(int step)
{
	if(step != m_initialStep)
		return;

	HumSettlers::process(step);

	int currShips = getResources(SHIPS);

	if(currShips > m_pioners.count())
	{
		HumShuttle* pioner = (HumShuttle*)UnitController::getInstance()->buildUnit(this, t_HUMAN_SHUTTLE);

		m_pionersInBase.push_back(pioner);
		m_pioners.push_back(pioner);
	}

	processUnits();
}

void HumColonyCenter::scanSectors()
{
	radar->scan();
	QList<Sector*>* sectorList = radar->getResults();


	if(!sectorList->isEmpty())
	{
		QList<Sector*>::iterator iter = sectorList->begin();
		QList<Sector*>::iterator end = sectorList->end();

		for( ; iter != end ; iter++)
		{
			Sector* sec = *iter;

			if(sec != nullptr)
			{
				Request* req = new Request();
				req->registred = false;
				req->resType = POPULATION;
				req->status = AWAITS;
				req->subject = sec;
				req->type = CONSUME;
				req->value = MIN_HUMAN_TO_MOVE;

				PlayerController::getInstance()->getPlayer(m_playerID)->addRequest(req);
			}
			else
			{
				qDebug() << "HumColonyCenter::scanSectors : Error! sec is null!";
			}
		}
	}
}

void HumColonyCenter::processUnits()
{
	if(!m_pionersInBase.isEmpty())
	{
		Request* provReq = m_player->getRequest(POPULATION, PROVIDE, getMapX(), getMapY());

		if(provReq == nullptr)
		{
			return;
		}

		Request* consReq = m_player->getRequest(POPULATION, CONSUME, getMapX(), getMapY());

		if(consReq == nullptr)
		{
			m_player->addRequest(provReq);

			//try to find new points to colonization
			scanSectors();
			return;
		}

		HumShuttle* pioner = m_pionersInBase.front();
		m_pionersInBase.pop_front();

		if(pioner != nullptr)
		{
			pioner->setRequest(provReq);
			pioner->setRequest(consReq);

			pioner->startUnit();
		}


	}

}

void HumColonyCenter::returnToBase(Unit *unit)
{
	if(unit != nullptr)
	{
		HumShuttle* pioner = (HumShuttle*) unit;
		m_pionersInBase.push_back(pioner);
	}
	else
	{
		qDebug() << "HumColonyCenter::returnToBase : Error! unit is null!";
	}
}
