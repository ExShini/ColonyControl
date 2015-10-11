#include "humshuttle.h"
#include "qdebug.h"
#include "Core/buildings/human/humcolonycenter.h"
#include "Core/objectcontroller.h"
#include "Core/objectstatecontroller.h"

HumShuttle::HumShuttle(UnitWrapper *wrapper, Building *base, int initialStep):
	Unit(wrapper, t_HUMAN_SHUTTLE, base, initialStep),
	m_source(nullptr),
	m_target(nullptr)
{
	setDirection(90);
	setSpeedInSectors(0.9);

	regResourse(POPULATION, 1000, 0);
    m_baseID = base->getID();
}

HumShuttle::~HumShuttle()
{

}

void HumShuttle::process(int step)
{
	Unit::process(step);
}

void HumShuttle::setRequest(Request *req)
{
	if(req->resType != POPULATION)
	{
		qDebug() << "HumShuttle::setRequest : wrang request! ResType : " << req->resType;
	}

	if(req->type == CONSUME)
	{
		if(m_target != nullptr)
		{
			qDebug() << "HumShuttle::setRequest wrong setup!";
		}

		m_target = req;
		m_target->status = IN_PROGRESS;
		if(m_target->subject->getType() != t_SECTOR)
		{
			m_targetID = m_target->subject->getID();
		}
		else
		{
			m_targetID = INVALIDE_VALUE;
		}
	}
	else if(req->type == PROVIDE)
	{
		m_source = req;
		m_source->status = IN_PROGRESS;

		if(m_source->subject != nullptr)
		{
			m_sourceID = m_source->subject->getID();
		}
	}
}

void HumShuttle::startUnit()
{
	if(m_source == nullptr || m_target == nullptr)
	{
		qDebug() << "HumShuttle::startUnit : Error! wrong request!";
	}

	Unit::startUnit();

	GObject* soursePoint = m_source->subject;

	m_specStatus = FIND_RESOURCES;
	setMapCourse(soursePoint->getMapX(), soursePoint->getMapY());
}

void HumShuttle::setMapCourse(int mapX, int mapY)
{
	// check: if we have enough resourses - return m_source request
	if(m_specStatus == FIND_RESOURCES)
	{
		int currentResVal = getResources(m_source->resType);
		int resLimit = getResLimit(m_source->resType);

		if(currentResVal >= resLimit)
		{
			m_source->status = AWAITS;
			m_source->registred = false;
			m_specStatus = SUPPLY_RESOURCES;

			Unit::setMapCourse(m_target->subject->getMapX(),
							   m_target->subject->getMapY());
			return;
		}
	}

	Unit::setMapCourse(mapX, mapY);

}

void HumShuttle::targetAchived()
{
	if(m_specStatus == FIND_RESOURCES)
	{
		bool status = getResFromTarget();

		if(status && m_target->status != NOT_ACTUAL)
		{
			m_specStatus = SUPPLY_RESOURCES;

			GObject* tarObj = m_target->subject;
			setMapCourse(tarObj->getMapX(), tarObj->getMapY());
		}
		else
		{
			flyToBase();
		}

	}
	else if(m_specStatus == SUPPLY_RESOURCES)
	{
		if(m_target == nullptr)
		{
			qDebug() << "HumShuttle::targetAchived : Error! m_target is null!";
            flyToBase();
            return;
		}

		if(m_target->subject == nullptr)
		{
			qDebug() << "HumShuttle::targetAchived : Error! subject is null!";
		}

		if(m_target->status == NOT_ACTUAL)
		{
			flyToBase();
			return;
		}

		OBJECT_TYPE objType = m_target->subject->getType();
		if(objType >= t_FIRST_SECTOR_TYPE && objType <= t_LAST_SECTOR_TYPE)
		{
			buildSettlement();
		}
		else
		{
			provideResToTarget();
		}

		flyToBase();

	}
	else if(m_specStatus == RETURN_TO_BASE)
	{
		returnToBase();
		m_status = ON_BASE;
		m_specStatus = NO_SPEC_STATUS;
	}
}

void HumShuttle::flyToBase()
{
    bool baseDestroyed = ObjectStateController::getInstance()->chackBuildingCondition(m_baseID, DESTROED_CONDITION);
    if(m_base != nullptr && !baseDestroyed)
	{
		m_specStatus = RETURN_TO_BASE;
		setMapCourse(m_base->getMapX(), m_base->getMapY());
	}
	else
	{
		qDebug() << "HumShuttle::flyToBase : base lost";
	}
}

void HumShuttle::buildSettlement()
{
	if(m_target == nullptr)
	{
		qDebug() << "HumShuttle::buildSettlement : Error! m_target is null!";
		return;
	}

	int population = getResources(POPULATION);

	Building* building = ObjectController::getInstance()->buildObj(
				t_HUMAN_SETTLERS,
				m_target->subject->getMapX(),
				m_target->subject->getMapY(),
				population, m_playerID);
	if(building != nullptr)
	{
		delete m_target;
		m_target = nullptr;

		setResources(POPULATION, 0);
	}
	else
	{
		qDebug() << "HumShuttle::buildSettlement : building is null";
	}
}

void HumShuttle::provideResToTarget()
{
	if(m_target != nullptr)
	{
		if(m_target->status == NOT_ACTUAL)
		{
			return;
		}

		if(m_target->value > 0)
		{
			RESOURSES resType = m_target->resType;
			int storageValue = getResources(resType);

			int resToProvide = 0;
			if(m_target->value < storageValue)
			{
				resToProvide = m_target->value;
			}
			else
			{
				resToProvide = storageValue;
			}

			Building* target = (Building*)m_target->subject;

			if(target != nullptr)
			{
				int id = target->getID();
				bool isDestroyed = ObjectStateController::getInstance()->chackBuildingCondition(id, DESTROED_CONDITION);

				if(target->getPlayerID() != m_playerID || isDestroyed)
				{
					delete m_target;
					m_target = nullptr;
					return;
				}

				int value = target->getResources(resType);

				value += resToProvide;
				target->setResources(resType, value);

				qDebug() << "HumShuttle::provideResToTarget : resToProvide " << resToProvide;

				m_target->value -= resToProvide;

				// set new res value for transport
				setResources(resType, storageValue - resToProvide);

				if(m_target->value <= 0)
				{
					target->requestComplited(resType);
					delete m_target;
				}
				else
				{
					m_target->status = AWAITS;
					m_target->registred = false;
				}

				m_target = nullptr;
			}
		}
	}
}

bool HumShuttle::getResFromTarget()
{
	if(m_source != nullptr)
	{
		if(m_source->status == NOT_ACTUAL)
		{
			delete m_source;
			return false;
		}

		RESOURSES resType = m_source->resType;
		int resToTake = m_source->value;
		int capasity = getResLimit(resType);
		int currentValue = getResources(resType);
		GObject* subject = m_source->subject;


		if(capasity == INVALIDE_VALUE)
		{
			qDebug() << "HumShuttle::getResFromTarget : unit (type:" << m_type <<
						":) cant take this resourse: " << m_source->resType;
			return false;
		}

		if(resToTake > (capasity - currentValue))
		{
			resToTake = capasity - currentValue;
		}

		qDebug() << "HumShuttle::getResFromTarget : resToTake " << resToTake;

		m_source->value -= resToTake;
		setResources(m_source->resType, resToTake + currentValue);


		if(m_source->value == 0)
		{
			m_source->subject->requestComplited(resType);
			delete m_source;
		}
		else
		{
			m_source->status = AWAITS;
			m_source->registred = false;
		}

		if(subject != nullptr)
		{
			int id = subject->getID();
			bool isDestroyed = ObjectStateController::getInstance()->chackBuildingCondition(id, DESTROED_CONDITION);


			if(!isDestroyed)
			{
				int subCurrValue = subject->getResources(resType);
				subject->setResources(resType, subCurrValue - resToTake);
			}
			else
			{
				return false;
			}
		}
		else
		{
			qDebug() << "HumShuttle::getResFromTarget : Error! subject is null!";
			return false;
		}

		m_source = nullptr;
	}

	return true;
}

void HumShuttle::returnToBase()
{
    bool baseDestroyed = ObjectStateController::getInstance()->chackBuildingCondition(m_baseID, DESTROED_CONDITION);
    if(baseDestroyed)
    {
        //TODO
        return;
    }

	Unit::returnToBase();
	HumColonyCenter* base = (HumColonyCenter*)m_base;

	base->returnToBase(this);
}
