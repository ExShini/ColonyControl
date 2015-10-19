#ifndef HUMCOLONYCENTER_H
#define HUMCOLONYCENTER_H
#include "humsettlers.h"
#include "Core/UnitController/Units/Human/humshuttle.h"
#include "Core/SubComponents/emptysectorradar.h"
#include "QList"

class HumColonyCenter: public HumSettlers
{
public:
	HumColonyCenter(GObjWrapper * wrapper,
					Sector *sector,
					int population,
					int initialStep,
					int plID);

	virtual ~HumColonyCenter();

	virtual void process(int step);
	virtual void returnToBase(Unit* unit);

protected:
	void processUnits();
	void scanSectors();

	QList<HumShuttle*> m_pionersInBase;
	QList<HumShuttle*> m_pioners;
	EmptySectorRadar* radar;
};

#endif // HUMCOLONYCENTER_H
