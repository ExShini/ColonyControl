#include "markercontroller.h"


/************************************************
 * Func: MarkerController
 * Desc: Constructor.
 ***********************************************/
MarkerController::MarkerController(QObject *parent) :
	QObject(parent),
	m_x(0),
	m_y(0),
	m_src(""),
	m_abilityMarkerSrc(""),
	m_visible(false)
{

}

/************************************************
 * Func: ~MarkerController
 * Desc: Destructor.
 ***********************************************/
MarkerController::~MarkerController()
{

}

/************************************************
 * Func: setX
 * Desc: Change position of x.
 ***********************************************/
void MarkerController::setX(int value)
{
	m_x = value;
	emit XChanged();
}

/************************************************
 * Func: setY
 * Desc: Change position of y.
 ***********************************************/
void MarkerController::setY(int value)
{
	m_y = value;
	emit YChanged();
}

/************************************************
 * Func: setSrc
 * Desc: Setup src for marker.
 ***********************************************/
void MarkerController::setSrc(QString src)
{
	m_src = src;
	emit srcChanged();
}

/************************************************
 * Func: setAbilityMarkerSrc
 * Desc: Setup src ability marker.
 ***********************************************/
void MarkerController::setAbilityMarkerSrc(QString src)
{
	m_abilityMarkerSrc = src;
	emit abilityMarkerChanged();
}

/************************************************
 * Func: setVisible
 * Desc: Setup visible for marker.
 ***********************************************/
void MarkerController::setVisible(bool value)
{
	m_visible = value;
	emit visibleChanged();
}
