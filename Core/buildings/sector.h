#ifndef SECTOR_H
#define SECTOR_H
#include "Core/gobject.h"
#include "Enums/mapsettings.h"

class Sector: public GObject
{
public:
	Sector();
	~Sector();

	int getFertility()          { return m_fertility; }
	int getMineralWealth()      { return m_mineralWealth; }
    int getNaturalResourse(RESOURSES resType);
	OBJECT_TYPE getType()		{ return m_type; }

	void setFertility(int value)        { m_fertility = value; }
	void setMineralWealth(int value)    { m_mineralWealth = value; }
	void setType(OBJECT_TYPE type);
	bool itApplicable()					{ return m_applicable; }

protected:

	int m_fertility;              //fertility for this sector. Food production depent of this parameter.
	int m_mineralWealth;          //maximum number of minerals, which can be base produced by settlers
	bool m_applicable;
};

#endif // SECTOR_H
