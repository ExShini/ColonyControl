#ifndef SMCONT_H
#define SMCONT_H
#include "QLinkedList"
#include "Enums/mapsettings.h"
#include "gobject.h"

typedef QLinkedList<GObject*>::iterator iter;
typedef QLinkedList<iter*>::iterator highIter;

class SmCont
{
public:
    SmCont();
    ~SmCont();


    void startIter();
    GObject* nextEl();
    QLinkedList<iter *> *getEl(int x, int y);
    void addEl(GObject * obj);
    void removeEl(GObject * obj);
	void moveElementFrom(GObject* obj, int oldX, int oldY);
	void clearAll(bool freeMemory = true);

	void finilizeProc(bool freeMemory = true);


protected:
    QLinkedList<GObject*> m_list;
    iter m_currEl;
    QLinkedList<iter*>* m_mapCont[MAP_WIDTH][MAP_HEIGHT];
    QLinkedList<iter*> m_toRemoved;


};

#endif // SMCONT_H
