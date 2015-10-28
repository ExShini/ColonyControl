#include "gobjwrapper.h"
#include "qdebug.h"

/************************************************
 * Func: GObjWrapper
 * Desc: constructor
 ***********************************************/
GObjWrapper::GObjWrapper(QObject *parent) :
	QObject(parent)
{

}

/************************************************
 * Func: ~GObjWrapper
 * Desc: destructor
 ***********************************************/
GObjWrapper::~GObjWrapper()
{

}

/************************************************
 * Func: setType
 * Desc: setup type for wrapper
 ***********************************************/
void GObjWrapper::setType(OBJECT_TYPE type)
{
    emit changeType((int)type);
}

/************************************************
 * Func: setLevel
 * Desc: setup level for wrapper
 ***********************************************/
void GObjWrapper::setLevel(int level, UI_STATES state)
{
	emit changeLevel(level, (int)state);
}

/************************************************
 * Func: setMarker
 * Desc: setup marker for wrapper
 ***********************************************/
void GObjWrapper::setMarker(int plID)
{
	emit changeMarker(plID);
}

/************************************************
 * Func: setEnabled
 * Desc: setup enabled state for wrapper
 ***********************************************/
void GObjWrapper::setEnabled()
{
    emit enable();
}

/************************************************
 * Func: setEnabled
 * Desc: setup disabled state for wrapper
 ***********************************************/
void GObjWrapper::setDisabled()
{
    emit disable();
}

/************************************************
 * Func: setSectorType
 * Desc: setup sector type for wrapper
 ***********************************************/
void GObjWrapper::setSectorType(OBJECT_TYPE type)
{
	emit changeSectorType((int)type);
}
