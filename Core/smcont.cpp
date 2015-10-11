#include "smcont.h"
#include "qdebug.h"

/************************************************
 * Func: SmCont
 * Desc: constructor
 ***********************************************/
SmCont::SmCont():
    m_list(),
    m_toRemoved()
{
    //initialize map-container
	for(int x = 0; x < MAP_WIDTH; x++)
    {
        for(int y = 0; y < MAP_HEIGHT; y++)
        {
			m_mapCont[x][y] = new QLinkedList<iter*>();
        }
    }
}

/************************************************
 * Func: SmCont
 * Desc: destructor
 ***********************************************/
SmCont::~SmCont()
{

}

/************************************************
 * Func: startIter
 * Desc: start new iteration of GObject's processing
 * Note: should be called whan we want to process all objects in cont
 ***********************************************/
void SmCont::startIter()
{
    if(m_list.count())
    {
        m_currEl = m_list.begin();
    }
    else
    {
        m_currEl = m_list.end();
    }
}

/************************************************
 * Func: nextEl
 * Desc: provide next element from container
 * Note: startIter should be called at start of the processinf loop
 ***********************************************/
GObject* SmCont::nextEl()
{
    GObject* value = nullptr;

    if(m_currEl != m_list.end())
    {
        value = *m_currEl;
        m_currEl++;

    }
    return value;
}


/************************************************
 * Func: getEl
 * Desc: return list of objects in x,y position
 ***********************************************/
QLinkedList<iter*>* SmCont::getEl(int x, int y)
{
    return m_mapCont[x][y];
}


/************************************************
 * Func: addEl
 * Desc: add new element to processing
 ***********************************************/
void SmCont::addEl(GObject * obj)
{
    m_list.push_front(obj);
    int x = obj->getMapX();
    int y = obj->getMapY();


	iter* it = new iter(m_list.begin());

	m_mapCont[x][y]->push_front(it);
}


/************************************************
 * Func: clearAll
 * Desc: clear container
 ***********************************************/
void SmCont::clearAll(bool freeMemory)
{
	startIter();
	GObject* obj = nextEl();

	while (obj != nullptr)
	{
		removeEl(obj);
		obj = nextEl();
	}

	finilizeProc(freeMemory);
}


/************************************************
 * Func: removeEl
 * Desc: remove element from container
 ***********************************************/
void SmCont::removeEl(GObject * obj)
{
    int x = obj->getMapX();
    int y = obj->getMapY();

    highIter it = m_mapCont[x][y]->begin();
    highIter end = m_mapCont[x][y]->end();

    for(; it != end ; it++)
    {
        iter* compIt = *it;
        GObject* compObj = *(*compIt);
        if(compObj == obj)
        {
            m_toRemoved.push_back(compIt);
            break;
        }
    }

	m_mapCont[x][y]->erase(it);
}

/************************************************
 * Func: moveElementFrom
 * Desc: move element from one position to new
 ***********************************************/
void SmCont::moveElementFrom(GObject *obj, int oldX, int oldY)
{
	int newX = obj->getMapX();
	int newY = obj->getMapY();
	bool successRemove = false;

	highIter it = m_mapCont[oldX][oldY]->begin();
	highIter end = m_mapCont[oldX][oldY]->end();
	iter* compIt = nullptr;

	// remove from ald cell
	for(; it != end ; it++)
	{
		compIt = *it;
		GObject* compObj = *(*compIt);
		if(compObj == obj)
		{
			m_mapCont[oldX][oldY]->erase(it);
			successRemove = true;
			break;
		}
	}

	if(!successRemove)
	{
		qDebug() << "SmCont::moveElementFrom: ERROR! Removing was failt!";
		return;
	}

	if(compIt == nullptr)
	{
		qDebug() << "SmCont::moveElementFrom: ERROR! compIt is null!";
		return;
	}

	//add to new cell

	m_mapCont[newX][newY]->push_front(compIt);
}

/************************************************
 * Func: finilizeProc
 * Desc: finalize loop. Clear mamory for all removed objects
 * Note: should be called at end of processing loop
 ***********************************************/
void SmCont::finilizeProc(bool freeMemory)
{
	iter* removedIt = nullptr;

	while(!m_toRemoved.isEmpty())
	{
		removedIt = m_toRemoved.front();
		GObject* removedObj = *(*removedIt);
		iter endIter = removedIt->operator +(1);
		m_list.erase(*removedIt, endIter);

		// deactivate if it still active
		removedObj->deactivate();
		if(freeMemory)
		{
			delete removedObj;
		}

		m_toRemoved.pop_front();
	}
}
