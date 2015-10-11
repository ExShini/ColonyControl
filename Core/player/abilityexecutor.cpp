#include "abilityexecutor.h"
#include "qdebug.h"

AbilityExecutor::AbilityExecutor(UnitWrapper *wrapper, OBJECT_TYPE type, int initialStep):
	Unit(wrapper, type, nullptr, initialStep),
	m_freeState(true)
{

}

AbilityExecutor::~AbilityExecutor()
{

}

void AbilityExecutor::process(int step)
{
	Unit::process(step);
}

void AbilityExecutor::activateAt(Building *building)
{
	// Should be implemented in subclasses
	Q_UNUSED(building);
	qDebug() << "AbilityExecutor::activateAt: Error! It should be implemented in subclasses!";
}
