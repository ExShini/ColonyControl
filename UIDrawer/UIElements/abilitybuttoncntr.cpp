#include "abilitybuttoncntr.h"
#include <QtQml>

AbilityButtonCntr::AbilityButtonCntr(ABILITY_TYPE type, int subType, QObject* parent):
	QObject(parent),
	m_type(type),
	m_subType(subType),
	m_state(INVALIDE_STATE)
{

}

AbilityButtonCntr::~AbilityButtonCntr()
{
	// Do no thing
}

void AbilityButtonCntr::regisrerTypes()
{
	qmlRegisterType<AbilityButtonCntr>(GAME_QML_PLAGIN, 1, 0, "AbilityCntr");
	qRegisterMetaType<AbilityButtonCntr::ABILITY_STATE>("AbilityCntr::ABILITY_STATE");
}

void AbilityButtonCntr::wasPressed()
{
	qDebug() << "AbilityButtonCntr::wasPressed()";
	emit pressedSignal(m_type, m_subType);
}

void AbilityButtonCntr::setSrc(QString src)
{
	m_src = src;
	emit srcChanged();
}

void AbilityButtonCntr::setDescription(QString description)
{
	description = description;
	emit descriptionChanged();
}

void AbilityButtonCntr::setCost(int cost)
{
	m_cost = cost;
	emit costChanged();
}

void AbilityButtonCntr::setstate(ABILITY_STATE state)
{
	m_state = state;
	emit stateChanged();
}
