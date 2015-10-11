#ifndef IONCANONSATELLITE_H
#define IONCANONSATELLITE_H
#include "../../abilityexecutor.h"
#include "ioncanonbullet.h"

class IonCanonSatellite: public AbilityExecutor
{
public:
	IonCanonSatellite(UnitWrapper *wrapper, int initialStep, int playerID);
	virtual ~IonCanonSatellite();
	virtual void activateAt(Building *building);
	virtual void process(int step);

protected:
	int m_flyTime;
	int m_widthOfFly;

	int m_latsSecX;
	int m_rotation;
	int m_currentAngle;

	int m_attackSecX;
	bool m_attack;

	IonCanonBullet* m_bullet;
};

#endif // IONCANONSATELLITE_H
