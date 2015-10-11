#ifndef HUMSETTLERS_H
#define HUMSETTLERS_H
#include "Core/buildings/building.h"
#include "Core/player/requestmanager.h"

class HumSettlers: public Building
{
public:
	HumSettlers(GObjWrapper * wrapper, Sector *sector, int population, int initialStep, int plID);
	virtual ~HumSettlers();

protected:
	virtual void process(int step);

	void popLimitEmigration();
	void foodEmigration();
	void immigrationReq(int colonists);

	short m_stateCount;

	Request* m_populationRequest;
};

#endif // HUMSETTLERS_H
