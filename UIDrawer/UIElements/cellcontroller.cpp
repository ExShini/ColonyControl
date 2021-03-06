#include <QtQml>
#include "cellcontroller.h"
#include "uiresdictionary.h"
#include "Core/randomgen.h"
#include "Enums/uistate.h"
#include "UIDrawer/uitimingmanager.h"
#include "qdebug.h"

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
    m_state = 0;	// NORMAL STATE
    m_animFrameCnt = 2;
    m_animFrameRate = 0.5;
    m_rowInFrame = 0;
    m_animSrc = QString("");
    m_backSrc = QString("/img/DefBackground.png");
    m_backDir = 0;
    m_markerSrc = QString("");
    m_curType = INVALID_OBJ_TYPE;
    m_timeToAnimate = 0;
	m_infinityLoop = true;
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
 * Func: backgroundDir
 * Desc: return direction for background image.
 ***********************************************/
int CellController::backgroundDir()
{
    return m_backDir;
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
 * Func: rowInFrame
 * Desc: return number of row in animation file.
 ***********************************************/
int CellController::rowInFrame()
{
    return m_rowInFrame;
}

/************************************************
 * Func: infinityLoop
 * Desc: return true for infinity loop and false for 1 loop animation.
 ***********************************************/
bool CellController::infinityLoop()
{
	return m_infinityLoop;
}

/************************************************
 * Func: setNewAnimation
 * Desc: setup new animation for cell.
 ***********************************************/
void CellController::setNewAnimation(QString src, int cnt, double rate, int row)
{
    m_animSrc = src;
    m_animFrameCnt = cnt;
    m_animFrameRate = rate;
    m_rowInFrame = row;

    emit animChanged();
	emit applyChanges();
}

/************************************************
 * Func: setNewBackground
 * Desc: setup new background image for cell.
 ***********************************************/
void CellController::setNewBackground(QString src)
{
    m_backSrc = src;
    // add random rotation for background
    m_backDir = (RandomGen::getRand() % 4) * 90;
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
void CellController::setLevel(int level, int state)
{
    int row = INVALIDE_VALUE;
    int frameCnt = INVALIDE_VALUE;
	double rate = INVALIDE_VALUE;

    m_level = level;
    bool tempState = (m_state != state) && (state != UI_NORMAL);
    m_state = state;
    QString src = UIResDictionary::getInstance()
			->getResource(m_curType, m_level, m_state, row, frameCnt, rate);

    if(tempState)
    {
		setTemproryState(frameCnt / rate);
    }

	setNewAnimation(src, frameCnt, rate, row);
}

void CellController::setTemproryState(double animationTime)
{
    double oldTime = m_timeToAnimate;
    m_timeToAnimate = animationTime;
	m_infinityLoop = false;

    if(oldTime == 0)
    {
        UITimingManager::getInstance()->addCCCntr(this);
    }
}

bool CellController::elapseTime(double time)
{
    bool continues = true;

    m_timeToAnimate -= time;
	if(m_timeToAnimate <= 0)	// trick
    {
        m_timeToAnimate = 0;
		m_infinityLoop = true;
        setState((int)UI_NORMAL);
        continues = false;
    }

    return continues;
}

/************************************************
 * Func: setType
 * Desc: setup new type for object. It also change animation src.
 ***********************************************/
void CellController::setType(int type)
{
    int row = INVALIDE_VALUE;
    int frameCnt = INVALIDE_VALUE;
	double rate = INVALIDE_VALUE;
    m_curType = (OBJECT_TYPE)type;
    QString src = UIResDictionary::getInstance()
			->getResource(m_curType, 0, 0, row, frameCnt, rate);

	setNewAnimation(src, frameCnt, rate, row);
}

void CellController::setState(int state)
{
    int row = INVALIDE_VALUE;
    int frameCnt = INVALIDE_VALUE;
	double rate = INVALIDE_VALUE;

	bool tempState = state != UI_NORMAL;

    m_state = state;
    QString src = UIResDictionary::getInstance()
			->getResource(m_curType, m_level, m_state, row, frameCnt, rate);

    if(tempState)
    {
		setTemproryState(frameCnt / rate);
    }

	setNewAnimation(src, frameCnt, rate, row);
}

/************************************************
 * Func: setSecType
 * Desc: setup new type for sector. It also change src for background.
 ***********************************************/
void CellController::setSecType(int type)
{
    // trick, it does not used
    int row = INVALIDE_VALUE;
    int frameCnt = INVALIDE_VALUE;
	double rate = INVALIDE_VALUE;

    OBJECT_TYPE bacType = (OBJECT_TYPE)type;
	QString src = UIResDictionary::getInstance()->getResource(bacType, 0, 0, row, frameCnt, rate);
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
