#include "ioncanonsatellite.h"
#include "Enums/procsettings/unitprocessing.h"
#include "Core/objectcontroller.h"
#include "Enums/coresettings.h"
#include "Core/UnitController/unitcontroller.h"

IonCanonSatellite::IonCanonSatellite(UnitWrapper *wrapper, int initialStep, int playerID):
	AbilityExecutor(wrapper, t_HUMAN_ION_CANON_SATELLITE, initialStep)
{
	m_flyTime = 4;
	m_widthOfFly = 15;
	m_rotation = 5;
	m_currentAngle = 0;

	float speed = (float)(m_widthOfFly - 1) / (float)(m_flyTime);

	m_bullet = (IonCanonBullet*) UnitController::getInstance()->buildAbilityExecutor(playerID, t_HUMAN_ION_CANON_BULLET);
	m_bullet->setDamage(1000);

	setMapCoord(0, 0, false);
	setSpeedInSectors(speed);
	m_active = false;
}

IonCanonSatellite::~IonCanonSatellite()
{

}

void IonCanonSatellite::activateAt(Building *building)
{
	if(building == nullptr)
		return;

	m_freeState = false;
	m_attack = false;

	m_attackSecX = building->getMapX();

	int startMapX = building->getMapX() - m_widthOfFly / 2;
	int startMapY = building->getMapY();

	int targetMapX = startMapX + m_widthOfFly - 1;

	// check coordinates
	if(startMapX < 0)
		startMapX = 0;

	if(targetMapX >= MAP_WIDTH)
		targetMapX = MAP_WIDTH - 1;


	m_currentAngle = 0;
	m_latsSecX = targetMapX;
	setMapCoord(startMapX, startMapY, true);
	setMapCourse(targetMapX, startMapY);
	setDirection(m_currentAngle);

	m_active = true;
	startUnit();
}

void IonCanonSatellite::process(int step)
{
	AbilityExecutor::process(step);


	int unitStep = (step + m_initialStep) % GAME_STEP_PER_SECOND;
	bool process = (unitStep % m_procStepSize) == 0;

	if(process && m_active)
	{
		m_currentAngle += m_rotation;
		if(m_currentAngle >= 360)
			m_currentAngle -= 360;

		setDirection(m_currentAngle);

		if(m_attackSecX == (getMapX() - 1) && !m_attack)
		{
			m_attack = true;
			int x = m_attackSecX;
			int y = getMapY();
			Building* target = ObjectController::getInstance()->getBuilding(x, y);

			if(target != nullptr)
			{
				m_bullet->setMapCoord(x, y, true);
				m_bullet->setTarget(target);
			}
		}
		else if(m_steps == 0)
		{
			returnToBase();
			m_freeState = true;
			m_active = false;
		}
	}
}
