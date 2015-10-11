#include "humtransportcenter.h"

HumTransportCenter::HumTransportCenter(GObjWrapper *wrapper, Sector *sector, int population, int initialStep, int plID):
	HumColonyCenter(wrapper, sector, population, initialStep, plID)
{
	m_type = t_HUMAN_TRANSPORT_CENTER;
	m_level = 0;

	m_wrapper->setType(m_type);
	m_wrapper->setLevel(0);
	m_wrapper->setEnabled();

	setResLimit(POPULATION, m_player->getResLimit(m_type, POPULATION, m_level));
	setResLimit(SUPPLY, m_player->getResLimit(m_type, SUPPLY, m_level));
	setResLimit(INFROSTRUCTURE, m_player->getResLimit(m_type, INFROSTRUCTURE, m_level + 1));

	setResLimit(SHIPS, m_player->getResLimit(m_type, SHIPS, m_level));


	m_maxLevel = HUMAN_MAX_TRANSPORT_CENTER_LEVEL;

	radar->setSetting(4, 3);
}

HumTransportCenter::~HumTransportCenter()
{

}
