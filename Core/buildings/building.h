#ifndef BUILDING_H
#define BUILDING_H
#include "Core/gobject.h"
#include "sector.h"
#include "Core/playercontroller.h"

class Building: public GObject
{
public:
	virtual void process(int step);
	virtual void deactivate();
	virtual void activate();
	virtual void removeWrapper();

	virtual ~Building();
	virtual void takeDamage(int damage);

protected:
	Building(GObjWrapper * wrapper, Sector *sector, int initialStep, int plID);
	virtual void checkState();

	Sector* m_sector;
	int m_initialStep;
	int m_level;
	int m_maxLevel;



	Player* m_player;
};

#endif // BUILDING_H
