#include "sector.h"

Sector::Sector():
	GObject(nullptr),
	m_fertility(0),
	m_mineralWealth(0),
	m_applicable(0)
{
}

Sector::~Sector()
{

}

void Sector::setType(OBJECT_TYPE type)
{
	m_type = type;

	if(type >= t_FIRST_NOT_APPLICABLE_TYPE && type <= t_LAST_NOT_APPLICABLE_TYPE)
	{
		m_applicable = false;
	}
	else
	{
		m_applicable = true;
	}
}
