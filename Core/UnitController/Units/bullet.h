#ifndef BULLET_H
#define BULLET_H
#include "unit.h"
#include "Enums/procsettings/unitprocessing.h"

class Bullet : public Unit
{
public:
	Bullet(UnitWrapper *wrapper, OBJECT_TYPE type , int initialStep);
	virtual ~Bullet();
	virtual void setDamage(int damage)		{ m_damage = damage / UNIT_PROC_RATE; }
	virtual void setTarget(GObject* target);

protected:
	int m_damage;
	GObject* m_target;
	int m_targetID;
};

#endif // BULLET_H
