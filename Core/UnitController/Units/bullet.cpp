#include "bullet.h"
#include "qdebug.h"

Bullet::Bullet(UnitWrapper *wrapper, OBJECT_TYPE type, int initialStep):
	Unit(wrapper, type, nullptr, initialStep),
	m_damage(0),
	m_target(nullptr),
	m_targetID(INVALIDE_VALUE)
{

}

Bullet::~Bullet()
{

}

void Bullet::setTarget(GObject* target)
{
	if(target != nullptr)
	{
		m_target = target;
		m_targetID = target->getID();
	}
	else
	{
		qDebug() << "Bullet::setTarget: Error! null target!";
	}

}
