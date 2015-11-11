#ifndef PLAYER_H
#define PLAYER_H
#include "Enums/objects.h"
#include "requestmanager.h"
#include "buildmanager.h"
#include "abilitymanager.h"
#include "Enums/races.h"
#include "Enums/guisettings.h"

#define NOT_SET 0

struct ResPrototype
{
    int defValue;
    Resourse* resorses [MAX_LEVEL];
};

struct ResPrototypeStotage
{
	OBJECT_TYPE type;
	int level;
	Resourse resorse;
};

struct DefResSetting
{
	OBJECT_TYPE type;
	RESOURSES resType;
	int defaulValue;
};

class Player
{
public:
	Player(int id, Race race);
	virtual ~Player();
	int m_ID;

	virtual void init();
	virtual int getResLimit(OBJECT_TYPE buildingType, RESOURSES res, int level);
	virtual Resourse* getResPrototype(OBJECT_TYPE buildingType, RESOURSES res, int level);
	virtual int getResDefaultValue(OBJECT_TYPE buildingType, RESOURSES res);

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
    void setResToPrototype(OBJECT_TYPE type, Resourse * res, int level);
    void setDefValue(OBJECT_TYPE type, RESOURSES resType, int defValue);

    ResPrototype* m_prototypes[NUM_OF_OBJ_TYPES][NUM_OF_RESOURSES];

	RequestManager* m_reqManager;
	BuildManager* m_builManager;
	AbilityManager* m_abilityManager;

	int m_mainResource;
	Race m_race;

	ABILITY_TYPE m_abilityType;
	int m_abilitySubType;
};

#endif // PLAYER_H
