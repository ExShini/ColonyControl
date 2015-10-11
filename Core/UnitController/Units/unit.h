#ifndef UNIT_H
#define UNIT_H
#include "Core/gobject.h"
#include "Core/UnitController/unitwrapper.h"
#include "Core/buildings/building.h"
#include "Enums/procsettings/humanunitprocessing.h"

class Unit: public GObject
{
public:
	Unit(UnitWrapper *wrapper, OBJECT_TYPE type, Building * base, int initialStep);
	virtual ~Unit();

	void setDirection(int direction);
	virtual void setMapCoord(int mapX, int mapY, bool teleport = false);
	virtual void setCoord(int x, int y, bool teleport = false);
	virtual void setMapCourse(int mapX, int mapY);
	virtual void setSpeedInSectors(float speedPerSecond);
	virtual float getSpeedInSectors();
	virtual void process(int step);
	virtual void deactivate();

	virtual int getMapX();
	virtual int getMapY();

	virtual bool isItChangePosition(int &oldMapX, int &oldMapY);
	virtual void unitWasMoved();

	virtual void startUnit();
	virtual void returnToBase();
	virtual void targetAchived();


protected:
	virtual void move();

	int m_direction;
	int m_xSpeed;
	int m_ySpeed;
	int m_steps;

	int m_targetX;
	int m_targetY;

	int m_capX;
	int m_capY;

	int m_speed;

	UnitWrapper* m_unitWrapper;
	Building* m_base;

	UNIT_STATUS m_status;
	SPECIAL_UNIT_STATUS m_specStatus;

	bool m_isChangePosition;
	int m_initialStep;
	int m_procStepSize;

	int m_oldMapXPos;
	int m_oldMapYPos;
};

#endif // UNIT_H
