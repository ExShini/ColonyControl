#include "uiunitcntr.h"
#include "UIDrawer/UIElements/uiresdictionary.h"

/************************************************
 * Func: UiUnitCntr()
 * Desc: Constructor.
 ***********************************************/
UiUnitCntr::UiUnitCntr(int id, QObject *parent):
	QObject(parent)
{
	m_id = id;
	m_active = false;
	m_visible = false;
	m_animFrameCnt = 2;
	m_animFrameRate = 0.5;
	m_animSrc = QString("");
	m_curType = INVALID_OBJ_TYPE;
	m_xPos = 0;
	m_yPos = 0;
	m_direction = 0;
}

/************************************************
 * Func: ~UiUnitCntr()
 * Desc: destructor.
 ***********************************************/
UiUnitCntr::~UiUnitCntr()
{

}

/************************************************
 * Func: animSrc()
 * Desc: return src for animation.
 ***********************************************/
QString UiUnitCntr::animSrc()
{
	return m_animSrc;
}

/************************************************
 * Func: isActive()
 * Desc: return state for animation.
 ***********************************************/
bool UiUnitCntr::isActive()
{
	return m_active;
}

/************************************************
 * Func: objIsvisible()
 * Desc: return visibility for animation.
 ***********************************************/
bool UiUnitCntr::objIsvisible()
{
	return m_visible;
}

/************************************************
 * Func: animFrameCnt()
 * Desc: return frame counter for animation.
 ***********************************************/
int UiUnitCntr::animFrameCnt()
{
	return m_animFrameCnt;
}

/************************************************
 * Func: animFrameRate()
 * Desc: return frame rate for animation.
 ***********************************************/
double UiUnitCntr::animFrameRate()
{
	return m_animFrameRate;
}

/************************************************
 * Func: setNewAnimation()
 * Desc: setup new animation for unit
 ***********************************************/
void UiUnitCntr::setNewAnimation(QString src, int cnt, double rate)
{
	m_animSrc = src;
	m_animFrameCnt = cnt;
	m_animFrameRate = rate;

	emit animChanged();
}

/************************************************
 * Func: disableObj()
 * Desc: setup disable state for unit. Also it hide animation.
 ***********************************************/
void UiUnitCntr::disableObj()
{
	m_active = false;
	m_visible = false;
	emit isActiveChanged();
	emit objIsvisibleChanged();
}

/************************************************
 * Func: enableObj()
 * Desc: setup enable state for unit. Also it show animation.
 ***********************************************/
void UiUnitCntr::enableObj()
{
	m_active = true;
	m_visible = true;
	emit isActiveChanged();
	emit objIsvisibleChanged();
}

/************************************************
 * Func: setLevel()
 * Desc: setup level for unit. Also it change animation.
 ***********************************************/
void UiUnitCntr::setLevel(int level)
{
	QString src = UIResDictionary::getInstance()->getResource(m_curType, level);

	setNewAnimation(src, 8, 4.0);
}

/************************************************
 * Func: setType()
 * Desc: setup type for unit. Also it change animation.
 ***********************************************/
void UiUnitCntr::setType(int type)
{
	m_curType = (OBJECT_TYPE)type;
	QString src = UIResDictionary::getInstance()->getResource(m_curType, 0);

	setNewAnimation(src, 8, 4.0);
}

/************************************************
 * Func: id()
 * Desc: return id
 ***********************************************/
int UiUnitCntr::id()
{
	return m_id;
}

/************************************************
 * Func: xPos()
 * Desc: return x position
 ***********************************************/
int UiUnitCntr::xPos()
{
	return m_xPos;
}

/************************************************
 * Func: yPos()
 * Desc: return y position
 ***********************************************/
int UiUnitCntr::yPos()
{
	return m_yPos;
}

/************************************************
 * Func: direction()
 * Desc: return direction for unit
 ***********************************************/
int UiUnitCntr::direction()
{
	return m_direction;
}

/************************************************
 * Func: setPosition()
 * Desc: setup position
 ***********************************************/
void UiUnitCntr::setPosition(int x, int y)
{
	m_xPos = x;
	m_yPos = y;

	emit posChanged();
}

/************************************************
 * Func: setDirection()
 * Desc: setup direction
 ***********************************************/
void UiUnitCntr::setDirection(int direction)
{
	m_direction = direction;
	emit directionChanged();
}
