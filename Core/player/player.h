#ifndef PLAYER_H
#define PLAYER_H
#include "Enums/objects.h"
#include "requestmanager.h"
#include "buildmanager.h"
#include "abilitymanager.h"
#include "Enums/races.h"
#include "Enums/guisettings.h"

class Player
{
public:
	Player(int id, Race race);
	virtual ~Player();
	int m_ID;

	virtual void init();
	virtual int getResLimit(OBJECT_TYPE buildingType, RESOURSES res, int level);

	void addRequest(Request* request);
	Request* getRequest(RESOURSES resType, REQ_TYPE reqType, int mapX, int mapY);

	virtual void changeMainResValue(int changeValue)	{ m_mainResource += changeValue; }
	virtual int getMainResValue()						{ return m_mainResource; }

	virtual bool activeAbility(int type, int subType);
	virtual void resetAbility();
	virtual bool applyAbilityAt(int x, int y);

	virtual void refreshAbility();
	virtual void objectWasDestroyed(Building* building);

protected:
	void setResLimit(OBJECT_TYPE type, RESOURSES res, int level, int value);

	int m_buildingLimits[NUM_OF_OBJ_TYPES][NUM_OF_RESOURSES][MAX_LEVEL];
	RequestManager* m_reqManager;
	BuildManager* m_builManager;
	AbilityManager* m_abilityManager;

	int m_mainResource;
	Race m_race;

	ABILITY_TYPE m_abilityType;
	int m_abilitySubType;
};

#endif // PLAYER_H