#include "unit.h"
#include "cmath"
#include "Enums/procsettings/unitprocessing.h"
#include "Enums/coresettings.h"
#include "../unitcontroller.h"

Unit::Unit(UnitWrapper *wrapper, OBJECT_TYPE type, Building * base, int initialStep):
	GObject(wrapper),
	m_direction(0),
	m_xSpeed(0),
	m_ySpeed(0),
	m_steps(0),
	m_targetX(0),
	m_targetY(0),
	m_capX(0),
	m_capY(0),
	m_speed(0),
	m_unitWrapper(wrapper),
	m_base(base),
	m_status(NO_UNIT_STATUS),
	m_specStatus(NO_SPEC_STATUS),
	m_isChangePosition(false),
	m_initialStep(initialStep),
	m_oldMapXPos(0),
	m_oldMapYPos(0)
{
	m_type = type;
	m_unitWrapper->setType(type);
	m_unitWrapper->setLevel(0, UI_NORMAL);
	m_procStepSize = GAME_STEP_PER_SECOND / UNIT_PROC_RATE;

	if(base != nullptr)
	{
		setMapCoord(m_base->getMapX(),m_base->getMapY(), false);
		m_playerID = base->getPlayerID();

		m_oldMapXPos = getMapX();
		m_oldMapYPos = getMapY();
	}
}

Unit::~Unit()
{

}

void Unit::setMapCoord(int mapX, int mapY, bool teleport)
{
	setCoord(GET_REAL_X(mapX), GET_REAL_Y(mapY), teleport);
}


void Unit::setCoord(int x, int y, bool teleport)
{
	if(teleport)
	{
		m_oldMapXPos = getMapX();
		m_oldMapYPos = getMapY();
	}

	m_isChangePosition = m_isChangePosition || teleport;

	m_x = x;
	m_y = y;

	m_unitWrapper->setPosition(m_x, m_y);
}

void Unit::setMapCourse(int mapX, int mapY)
{
	int targetX = GET_REAL_X(mapX);
	int targetY = GET_REAL_Y(mapY);

	int xShift = targetX - m_x;
	int yShift = targetY - m_y;

	if(xShift == 0 && yShift == 0)
	{
		m_steps = 0;
		m_direction = 0;
		m_xSpeed = 0;
		m_ySpeed = 0;

		return;
	}
	else
	{
		m_steps = (sqrt(pow(xShift, 2) + pow(yShift, 2)) * UNIT_PROC_RATE) / m_speed;
	}

	if(xShift != 0)
	{
		//calc angle
		double radAng = atan((double)(yShift) / ((double)xShift));
		m_direction = radAng * RAD1;
	}
	else if (yShift >= 0)
	{
		m_direction = 90;
	}
	else if (yShift < 0)
	{
		m_direction = 270;
	}

	if(xShift < 0)
	{
		m_direction += 180;
	}

	if(m_steps != 0)
	{
		m_xSpeed = (ADD_ACCURACY_FACTOR(xShift)) / m_steps;
		m_ySpeed = (ADD_ACCURACY_FACTOR(yShift)) / m_steps;
	}

	m_unitWrapper->setDirection(m_direction);
}

void Unit::process(int step)
{
	int unitStep = (step + m_initialStep) % GAME_STEP_PER_SECOND;
	bool process = (unitStep % m_procStepSize) == 0;

	if(process)
	{
		move();
	}
}

void Unit::unitWasMoved()
{
	m_isChangePosition = false;
	m_oldMapXPos = getMapX();
	m_oldMapYPos = getMapY();
}

void Unit::move()
{
	// if we still must fly to target
	if(m_steps > 0)
	{

		m_capX += m_xSpeed;
		m_capY += m_ySpeed;

		int xStepShift = REMOVE_ACCURACY_FACTOR(m_capX);
		int yStepShift = REMOVE_ACCURACY_FACTOR(m_capY);

		m_x += xStepShift;
		m_y += yStepShift;

		m_capX -= ADD_ACCURACY_FACTOR(xStepShift);
		m_capY -= ADD_ACCURACY_FACTOR(yStepShift);

		m_steps--;

		m_unitWrapper->setPosition(m_x, m_y);

		//check - should we change position in unit smCount

		//m_isChangePosition = false;
		if(getMapX() != m_oldMapXPos || getMapY() != m_oldMapYPos)
		{
			m_isChangePosition = true;
		}
	}
	else
	{
		targetAchived();
	}
}

void Unit::targetAchived()
{
	// Do nothing
}

void Unit::setSpeedInSectors(float speedPerSecond)
{
	m_speed = CONVERT_SECTORS_TO_PXL(speedPerSecond);
}

float Unit::getSpeedInSectors()
{
	return CONVERT_PXL_TO_SECTORS(m_speed);
}

void Unit::setDirection(int direction)
{
	m_direction = direction;
	m_unitWrapper->setDirection(direction);
}

void Unit::deactivate()
{
	m_unitWrapper->setDirection(0);
	m_unitWrapper->setPosition(0,0);

	GObject::deactivate();

	UnitController::getInstance()->returnUnitWrapper(m_unitWrapper);

	m_wrapper = nullptr;
	m_unitWrapper = nullptr;
}

int Unit::getMapX()
{
	int centerX = m_x + (CELL_MAP_WIDTH >> 1);
	return GET_MAP_X(centerX); // GET_MAP_X(m_x + (CELL_MAP_WIDTH / 2))
}

int Unit::getMapY()
{
	int centerY = m_y + (CELL_MAP_HEIGHT >> 1);
	return GET_MAP_Y(centerY); // GET_MAP_Y(m_y + (CELL_MAP_HEIGHT / 2))
}

bool Unit::isItChangePosition(int &oldMapX, int &oldMapY)
{
	oldMapX = m_oldMapXPos;
	oldMapY = m_oldMapYPos;
	return m_isChangePosition;
}

void Unit::startUnit()
{
	m_wrapper->setEnabled();
	m_status = OPERATION;
}

void Unit::returnToBase()
{
	m_wrapper->setDisabled();
}
