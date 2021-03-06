#ifndef GOBJECT
#define GOBJECT
#include "Enums/objects.h"
#include "Enums/mapsettings.h"
#include "Enums/uistate.h"
#include "QMap"

class GObjWrapper;
class Request;

class GObject
{
public:
	GObject(GObjWrapper * wrapper);
	virtual ~GObject();

	virtual int getX() { return m_x; }
	virtual int getY() { return m_y; }
	virtual int getMapX() { return GET_MAP_X(m_x); }
	virtual int getMapY() { return GET_MAP_Y(m_y); }
	virtual int getID()	{ return m_id; }
	int getPlayerID()	{ return m_playerID; }


	virtual OBJECT_TYPE getType() { return m_type; }


	virtual void setCoord(int x, int y);
	virtual void setMapCoord(int x, int y);
	virtual void setID(int id)	{ m_id = id; }
	virtual void process(int step) { Q_UNUSED(step) /* do nothing */ }

	int setResources(RESOURSES type, int value);
	void setResProgress(RESOURSES type, int progValue);
	int getResources(RESOURSES type);
	Resourse* getResourcesObj(RESOURSES type);
	void setResLimit(RESOURSES type, int value);
	int getResLimit(RESOURSES type);

	void resetIteration();
	bool getNextResource(RESOURSES& type, Resourse &value);

	virtual void addRequst(Request* req);
	void requestComplited(RESOURSES resType);
	Request* getRequest(RESOURSES resType);

	void virtual deactivate();
	bool isActive()				{ return m_active; }
	virtual void takeDamage(int damage);

protected:
	virtual void regResourse(RESOURSES type, int maxValue, int defValue = 0, bool hard = true);
	virtual void regResourse(RESOURSES type);
	virtual void updateResourse(RESOURSES type, int level, bool initial = false);

	GObjWrapper* m_wrapper;
	bool m_active;

	int m_x;
	int m_y;
	OBJECT_TYPE m_type;
	int m_id;
	QMap<RESOURSES, Resourse*> m_resources;
	QMap<RESOURSES, Request*> m_requestMap;

	QMap<RESOURSES, Resourse*>::iterator m_curResource;

	int m_level;
	int m_playerID;

};

#endif // GOBJECT

