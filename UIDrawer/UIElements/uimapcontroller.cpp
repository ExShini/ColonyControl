#include "uimapcontroller.h"
#include "QQmlContext"
#include "QtQml"
#include "Enums/guisettings.h"

UIMapController* UIMapController::s_instance = nullptr;


/************************************************
 * Func: UIMapController(QObject *parent)
 * Desc: Constructor.
 ***********************************************/
UIMapController::UIMapController(QObject *parent):
	QObject(parent),
	m_cnt(1),
	m_boarderWidth(1)
{
	//create cellControllers map
	for(int i = 0; i < MAP_WIDTH; i++ )
	{
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			int id = i * MAP_WIDTH + j;
			m_cellCntrs[i][j] = new CellController(id);
			m_cellCntrs[i][j]->enableObj();
		}
	}

	m_markerCntr = new MarkerController();
	m_markerCntr->setSrc(DEFAULT_MOUSE_MARKER);
}


/************************************************
 * Func: getInstance()
 * Desc: Singleton implementation.
 ***********************************************/
UIMapController * UIMapController::getInstance()
{
	if(s_instance == nullptr)
	{
		s_instance = new UIMapController();
	}

	return s_instance;
}

/************************************************
 * Func: setFocus(int id)
 * Desc: Set focus for current cell and translate data to screen
 ***********************************************/
void UIMapController::setFocus(int id)
{
	int y = id % MAP_WIDTH;
	int x = id / MAP_WIDTH;

	m_markerCntr->setX(x * CELL_MAP_WIDTH);
	m_markerCntr->setY(y * CELL_MAP_HEIGHT);

	emit focusChanged(x, y);
}

/************************************************
 * Func: setEngine(QQmlApplicationEngine *engine)
 * Desc: Set engine to UIMapController
 ***********************************************/
void UIMapController::setEngine(QQmlApplicationEngine *engine)
{
	m_engine = engine;
}

/************************************************
 * Func: getCCntr()
 * Desc: Return controller to current qml cell
 ***********************************************/
CellController* UIMapController::getCCntr()
{
	CellController* cc = m_cellCntrs[m_i][m_j];
	if(cc == nullptr)
	{
		qDebug() << "Error!";
	}
	return cc;
}

/************************************************
 * Func: getCCntr(int x, int y)
 * Desc: Return controller to current qml cell
 ***********************************************/
CellController* UIMapController::getCCntrByCor(int x, int y)
{
	return m_cellCntrs[x][y];
}

/************************************************
 * Func: init()
 * Desc: Initialize all internal stuf. Also it create cell to map.
 ***********************************************/
void UIMapController::init()
{
	//if engine is null - ERROR!
	if(m_engine == nullptr)
	{
		qDebug() << "UIMapController::init: Engine doesn't set!";
		return;
	}

	InitCells();
	InitMarker();

}

/************************************************
 * Func: registerComponent()
 * Desc: Register UIMapController's class for QML usage.
 ***********************************************/
void UIMapController::registerComponent()
{
	m_engine->rootContext()->setContextProperty("MapController", this);

	qmlRegisterType<CellController>(GAME_QML_PLAGIN, 1, 0, "CControl");
	qmlRegisterType<MarkerController>(GAME_QML_PLAGIN, 1, 0, "MarkerCntr");
}

/************************************************
 * Func: InitCells()
 * Desc: Initialize cells components.
 ***********************************************/
void UIMapController::InitCells()
{
	QQmlComponent component(m_engine
							, QUrl(QStringLiteral("qrc:/res/MapItem.qml")));

	if(component.status() == QQmlComponent::Error)
	{
		qDebug() << "Error: " << component.errorString();
	}


	QList<QObject*> list = m_engine->rootObjects();


	QObject* mapAreaObj = list[0]->findChild<QObject*>("mapArea");
	QQuickItem *itemMap = qobject_cast<QQuickItem*>(mapAreaObj);

	itemMap->setProperty("contentWidth", CELL_MAP_WIDTH * MAP_WIDTH);
	itemMap->setProperty("contentHeight", CELL_MAP_HEIGHT * MAP_HEIGHT);


	for(m_i = 0; m_i < MAP_WIDTH; m_i++)
	{
		for(m_j = 0; m_j < MAP_HEIGHT; m_j++)
		{
			QObject *object = component.create();
			QQuickItem * item = qobject_cast<QQuickItem*>(object);
			item->setWidth(CELL_MAP_WIDTH);
			item->setHeight(CELL_MAP_HEIGHT);
			item->setX(CELL_MAP_WIDTH * m_i);
			item->setY(CELL_MAP_HEIGHT * m_j);


			item->setParentItem(itemMap->childItems()[0]);

			m_cellUIObj[m_i][m_j] = item;
		}
	}
}

/************************************************
 * Func: InitMarker()
 * Desc: Initialize marker component.
 ***********************************************/
void UIMapController::InitMarker()
{
	QQmlComponent component(m_engine
							, QUrl(QStringLiteral("qrc:/res/CellMarker.qml")));

	if(component.status() == QQmlComponent::Error)
	{
		qDebug() << "Error: " << component.errorString();
	}

	QList<QObject*> list = m_engine->rootObjects();


	QObject* mapAreaObj = list[0]->findChild<QObject*>("mapArea");
	QQuickItem *itemMap = qobject_cast<QQuickItem*>(mapAreaObj);


	QObject *object = component.create();
	QQuickItem * item = qobject_cast<QQuickItem*>(object);
	item->setWidth(CELL_MAP_WIDTH);
	item->setHeight(CELL_MAP_HEIGHT);
	item->setX(0);
	item->setY(0);


	item->setParentItem(itemMap->childItems()[0]);

}

/************************************************
 * Func: getMarkerContr()
 * Desc: return MarkerController.
 ***********************************************/
MarkerController* UIMapController::getMarkerContr()
{
	return m_markerCntr;
}

/************************************************
 * Func: startGame()
 * Desc: Prepare components for new game.
 ***********************************************/
void UIMapController::startGame()
{
	m_markerCntr->setVisible(true);
}
