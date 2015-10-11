#include <QtQml>
#include "cellcontroller.h"
#include "uiresdictionary.h"

/************************************************
 * Func: CellController
 * Desc: Constructor.
 ***********************************************/
CellController::CellController(int id, QObject *parent) :
    QObject(parent)
{
	m_id = id;
    m_active = false;
    m_visible = false;
    m_animFrameCnt = 2;
    m_animFrameRate = 0.5;
    m_animSrc = QString("");
	m_backSrc = QString("/img/DefBackground.png");
	m_markerSrc = QString(""),
    m_curType = INVALID_OBJ_TYPE;
}

/************************************************
 * Func: ~CellController
 * Desc: destructor.
 ***********************************************/
CellController::~CellController()
{

}

/************************************************
 * Func: mainObjAnimSrc
 * Desc: return src for main cell animation.
 ***********************************************/
QString CellController::mainObjAnimSrc()
{
    return m_animSrc;
}

/************************************************
 * Func: backgroundSrc
 * Desc: return src for background image.
 ***********************************************/
QString CellController::backgroundSrc()
{
	return m_backSrc;
}

/************************************************
 * Func: markerSrc
 * Desc: return src for player marker image.
 ***********************************************/
QString CellController::markerSrc()
{
	return m_markerSrc;
}

/************************************************
 * Func: isActive
 * Desc: return state for animation.
 ***********************************************/
bool CellController::isActive()
{
    return m_active;
}

/************************************************
 * Func: objIsvisible
 * Desc: return visibility for animation.
 ***********************************************/
bool CellController::objIsvisible()
{
    return m_visible;
}

/************************************************
 * Func: mainObjAnimFrameCnt
 * Desc: return frame conter for animation.
 ***********************************************/
int CellController::mainObjAnimFrameCnt()
{
    return m_animFrameCnt;
}

/************************************************
 * Func: mainObjAnimFrameRate
 * Desc: return frame rate for animation.
 ***********************************************/
double CellController::mainObjAnimFrameRate()
{
    return m_animFrameRate;
}

/************************************************
 * Func: setNewAnimation
 * Desc: setup new animation for cell.
 ***********************************************/
void CellController::setNewAnimation(QString src, int cnt, double rate)
{
    m_animSrc = src;
    m_animFrameCnt = cnt;
    m_animFrameRate = rate;

    emit animChanged();
}

/************************************************
 * Func: setNewBackground
 * Desc: setup new background image for cell.
 ***********************************************/
void CellController::setNewBackground(QString src)
{
	m_backSrc = src;
	emit backChanged();
}

/************************************************
 * Func: setPlayerMarker
 * Desc: setup new marker image for cell.
 ***********************************************/
void CellController::setPlayerMarker(int playerID)
{
	m_markerSrc = UIResDictionary::getInstance()->getMarkerSrc(playerID);
	emit markerChanged();
}

/************************************************
 * Func: disableObj
 * Desc: disable object and hide cell's animation.
 ***********************************************/
void CellController::disableObj()
{
    m_active = false;
    m_visible = false;
    emit isActiveChanged();
}

/************************************************
 * Func: enableObj
 * Desc: enable object and show cell's animation.
 ***********************************************/
void CellController::enableObj()
{
    m_active = true;
    m_visible = true;
    emit isActiveChanged();
    emit objIsvisibleChanged();
}

/************************************************
 * Func: setLevel
 * Desc: setup new level for object. It also change animation src.
 ***********************************************/
void CellController::setLevel(int level)
{
    QString src = UIResDictionary::getInstance()->getResource(m_curType, level);

    setNewAnimation(src, 8, 4.0);
}

/************************************************
 * Func: setType
 * Desc: setup new type for object. It also change animation src.
 ***********************************************/
void CellController::setType(int type)
{
    m_curType = (OBJECT_TYPE)type;
    QString src = UIResDictionary::getInstance()->getResource(m_curType, 0);

    setNewAnimation(src, 8, 4.0);
}

/************************************************
 * Func: setSecType
 * Desc: setup new type for sector. It also change src for background.
 ***********************************************/
void CellController::setSecType(int type)
{
	OBJECT_TYPE bacType = (OBJECT_TYPE)type;
	QString src = UIResDictionary::getInstance()->getResource(bacType, 0);
	setNewBackground(src);
}


/************************************************
 * Func: id
 * Desc: return id of cell.
 ***********************************************/
int CellController::id()
{
	return m_id;
}
