#include "ioncanonbullet.h"
#include "Enums/procsettings/unitprocessing.h"
#include "Enums/coresettings.h"
#include "Core/objectstatecontroller.h"

IonCanonBullet::IonCanonBullet(UnitWrapper *wrapper, int initialStep):
	Bullet(wrapper, t_HUMAN_ION_CANON_BULLET, initialStep)
{
	m_lastStep = (UNIT_PROC_RATE * 2) - 1;
	m_anglePerStep = 5;
}

IonCanonBullet::~IonCanonBullet()
{

}

void IonCanonBullet::setTarget(GObject *target)
{
	Bullet::setTarget(target);

	m_angle = 0;
	m_step = 0;
	startUnit();
}

void IonCanonBullet::process(int step)
{
	int unitStep = (step + m_initialStep) % GAME_STEP_PER_SECOND;
	bool process = (unitStep % m_procStepSize) == 0;

	if(!process)
		return;

	if(m_step >= m_lastStep)
	{
		m_target = nullptr;
		m_targetID = INVALIDE_VALUE;
		returnToBase();
		return;
	}

	if(m_target != nullptr && m_targetID != INVALIDE_VALUE)
	{
		// check, what it is still alive
		bool state = ObjectStateController::getInstance()->chackBuildingCondition(m_targetID, DESTROED_CONDITION);
		if(!state)
		{
			m_target->takeDamage(m_damage);
		}
	}
	else
	{
		return;
	}

	setDirection(m_angle);

	m_angle += m_anglePerStep;
	m_step++;
}
