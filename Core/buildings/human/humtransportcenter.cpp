#include "humtransportcenter.h"

HumTransportCenter::HumTransportCenter(GObjWrapper *wrapper, Sector *sector, int population, int initialStep, int plID):
	HumColonyCenter(wrapper, sector, population, initialStep, plID)
{
	m_type = t_HUMAN_TRANSPORT_CENTER;

	m_wrapper->setType(m_type);
	m_wrapper->setLevel(1, UI_NORMAL);
	m_wrapper->setEnabled();

	updateResourse(POPULATION, m_level);
	updateResourse(SUPPLY, m_level);
	updateResourse(INFROSTRUCTURE, m_level);
	updateResourse(SHIPS, m_level, true);

	m_maxLevel = HUMAN_MAX_TRANSPORT_CENTER_LEVEL;

	radar->setSetting(4, 3);
}

HumTransportCenter::~HumTransportCenter()
{

}
