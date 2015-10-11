#ifndef HUMSHUTTLE_H
#define HUMSHUTTLE_H
#include "../unit.h"

class HumShuttle: public Unit
{
public:
	HumShuttle(UnitWrapper *wrapper, Building * base, int initialStep);
	~HumShuttle();

	virtual void process(int step);

	void setRequest(Request* req);
	virtual void startUnit();
	virtual void returnToBase();
	virtual void setMapCourse(int mapX, int mapY);

protected:
	virtual void targetAchived();
	virtual bool getResFromTarget();
	virtual void provideResToTarget();
	virtual void buildSettlement();
	virtual void flyToBase();


	Request * m_source;
	Request * m_target;

    int m_baseID;
	int m_targetID;
	int m_sourceID;
};

#endif // HUMSHUTTLE_H
