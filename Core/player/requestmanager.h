#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H
#include "Enums/objects.h"
#include "Enums/gameprocessingsettings.h"
#include "QList"

class GObject;

struct Request
{
	bool			registred;
	RESOURSES		resType;
	REQ_STATUS		status;
	REQ_TYPE		type;
	int				value;
	GObject*		subject;

	Request():
		registred(false),
		resType(NO_RES),
		status(NO_REQ_STATUS),
		type(NO_REQ_TYPE),
		value(0)
	{}
};


class RequestManager
{
public:
	RequestManager();
	void addRequest(Request* request);

	Request* findRequest(RESOURSES resType, REQ_TYPE reqType, int mapX, int mapY);
	Request* getRequestFrom(int x, int y, RESOURSES resType, REQ_TYPE reqType);

protected:
	QList<Request*>* m_requests[NUM_OF_RESOURSES][NUM_OF_REQ_TYPE][NUM_OF_SECTOR_AT_WIDTH][NUM_OF_SECTOR_AT_HEIGHT];
	QList<Request*> m_reqAtExecution;
};

#endif // REQUESTMANAGER_H
