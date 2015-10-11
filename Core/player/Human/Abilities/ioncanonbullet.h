#ifndef IONCANONBULLET_H
#define IONCANONBULLET_H
#include "Core/UnitController/Units/bullet.h"

class IonCanonBullet: public Bullet
{
public:
	IonCanonBullet(UnitWrapper *wrapper, int initialStep);
	virtual ~IonCanonBullet();
	virtual void process(int step);
	virtual void setTarget(GObject *target);

protected:
	int m_step;
	int m_lastStep;
	int m_angle;
	int m_anglePerStep;
};

#endif // IONCANONBULLET_H
