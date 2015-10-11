#include "requestmanager.h"
#include "Core/gobject.h"
#include "qdebug.h"

RequestManager::RequestManager():
	m_reqAtExecution()
{
	for(int res = FIRST_RES; res < LAST_RES; res++)
	{
		for(int i = 0; i < NUM_OF_SECTOR_AT_WIDTH; i++)
		{
			for(int j = 0; j < NUM_OF_SECTOR_AT_HEIGHT; j++)
			{
				for(int reqType = 0; reqType < NUM_OF_REQ_TYPE; reqType++)
				{
					m_requests[res][reqType][i][j] = new QList<Request*>();
				}

			}
		}
	}
}

void RequestManager::addRequest(Request *request)
{
//	qDebug() << "RequestManager::addRequest: request: res:" << request->resType <<
//				" status:" << request->status <<
//				" value:" << request->value;

	int resType = request->resType;

	//determine trade sector position
	GObject* sub = request->subject;
	int sectorX = sub->getMapX() / REQUEST_SECTOR_WIDTH;
	int sectorY = sub->getMapY() / REQUEST_SECTOR_WIDTH;
	int reqType = request->type;

	if(reqType == NO_REQ_TYPE || resType == NO_RES)
	{
		qDebug() << "RequestManager::addRequest : ERROR! reqType or resType is invalid!";
		return;
	}

	QList<Request*>* reqList = m_requests[resType][reqType][sectorX][sectorY];
	reqList->push_back(request);
	request->registred = true;	// set registration to true
}

Request* RequestManager::findRequest(RESOURSES resType, REQ_TYPE reqType, int mapX, int mapY)
{
	Request* req = nullptr;

	int sectorX = mapX / REQUEST_SECTOR_WIDTH;
	int sectorY = mapY / REQUEST_SECTOR_WIDTH;

	//center sector
	req = getRequestFrom(sectorX, sectorY, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	//top sector
	req = getRequestFrom(sectorX, sectorY - 1, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	//bottom sector
	req = getRequestFrom(sectorX, sectorY + 1, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	//left sector
	req = getRequestFrom(sectorX - 1, sectorY, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	//right sector
	req = getRequestFrom(sectorX + 1, sectorY, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	//right-top sector
	req = getRequestFrom(sectorX + 1, sectorY - 1, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	//right-bottom sector
	req = getRequestFrom(sectorX + 1, sectorY + 1, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	//left-bottom sector
	req = getRequestFrom(sectorX - 1, sectorY + 1, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	//left-top sector
	req = getRequestFrom(sectorX - 1, sectorY - 1, resType, reqType);
	if(req != nullptr)
	{
		return req;
	}

	return req;
}

Request* RequestManager::getRequestFrom(int x, int y, RESOURSES resType, REQ_TYPE reqType)
{
	QList<Request*>* list;
	Request* req = nullptr;

	int width = NUM_OF_SECTOR_AT_WIDTH;
	int heigth = NUM_OF_SECTOR_AT_HEIGHT;

	if(x >= 0 && x < width && y >= 0 && y < heigth)
	{
		list = m_requests[resType][reqType][x][y];

		if(!list->isEmpty())
		{
			req = list->front();
			list->pop_front();

			m_reqAtExecution.push_back(req);

			return req;
		}
	}

	return req;

//	if(x < 0 && x >= NUM_OF_SECTOR_AT_WIDTH - 1)
//		return nullptr;

//	if(y < 0 && y >= NUM_OF_SECTOR_AT_HEIGHT - 1)
//		return nullptr;

}
