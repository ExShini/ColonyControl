#include "QQmlContext.h"
#include "uiunitcontroller.h"
#include "Enums/mapsettings.h"

UiUnitController* UiUnitController::s_instance = nullptr;

/************************************************
 * Func: UiUnitController
 * Desc: Constructor
 ***********************************************/
UiUnitController::UiUnitController(QObject *parent)
	: QObject(parent)
{
	for(int id = 0; id < MAX_NUMBER_OF_UNITS; id++)
	{
		m_unitControllers[id] = new UiUnitCntr(id, this);
	}
}

/************************************************
 * Func: ~UiUnitController
 * Desc: Destructor
 ***********************************************/
UiUnitController::~UiUnitController()
{

}

/************************************************
 * Func: ~UiUnitController
 * Desc: Destructor
 ***********************************************/
UiUnitController* UiUnitController::getInstance()
{
	if(s_instance == nullptr)
	{
		s_instance = new UiUnitController();
	}

	return s_instance;
}

/************************************************
 * Func: setEngine(QQmlApplicationEngine *engine)
 * Desc: Set engine to UiUnitController
 ***********************************************/
void UiUnitController::setEngine(QQmlApplicationEngine *engine)
{
	m_engine = engine;
}

/************************************************
 * Func: init
 * Desc: initialize UiUnitController's staff
 ***********************************************/
void UiUnitController::init()
{
	//if engine is null - ERROR!
	if(m_engine == nullptr)
	{
		qDebug() << "UIMapController::init: Engine doesn't set!";
		return;
	}

	initUIUnitElements();
}

/************************************************
 * Func: registerComponent
 * Desc: registerComponent UiUnitController's classes for QML usage
 ***********************************************/
void UiUnitController::registerComponent()
{
	qmlRegisterType<UiUnitCntr>(GAME_QML_PLAGIN, 1, 0, "UiUnitCntr");
	m_engine->rootContext()->setContextProperty("UiUnitController", this);
}

/************************************************
 * Func: initUIUnitElements
 * Desc: prepare ui elements
 ***********************************************/
void UiUnitController::initUIUnitElements()
{
	QQmlComponent component(m_engine
							, QUrl(QStringLiteral("qrc:/res/UnitItem.qml")));

	if(component.status() == QQmlComponent::Error)
	{
		qDebug() << "Error: " << component.errorString();
	}


	QList<QObject*> list = m_engine->rootObjects();


	QObject* mapAreaObj = list[0]->findChild<QObject*>("mapArea");
	QQuickItem *itemMap = qobject_cast<QQuickItem*>(mapAreaObj);

	for(m_unitId = 0; m_unitId < MAX_NUMBER_OF_UNITS; m_unitId++)
	{
		QObject *object = component.create();
		QQuickItem * item = qobject_cast<QQuickItem*>(object);
		item->setWidth(CELL_MAP_WIDTH);
		item->setHeight(CELL_MAP_HEIGHT);
		item->setX(0);
		item->setY(0);

		item->setProperty("unitID", m_unitId);
		item->setParentItem(itemMap->childItems()[0]);

		m_unitUIObj[m_unitId] = item;
	}
}

/************************************************
 * Func: getUnitCntr
 * Desc: return UiUnitCntr to qml element
 ***********************************************/
UiUnitCntr* UiUnitController::getUnitCntr()
{
	UiUnitCntr* uiContr =  m_unitControllers[m_unitId];
	return uiContr;
}

/************************************************
 * Func: getUnitCntr
 * Desc: return UiUnitCntr by unit id
 ***********************************************/
UiUnitCntr* UiUnitController::getUnitCntr(int id)
{
	UiUnitCntr* uiContr =  m_unitControllers[id];
	return uiContr;
}
