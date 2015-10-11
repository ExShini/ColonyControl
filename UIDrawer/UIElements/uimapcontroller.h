#ifndef UIMAPCONTROLLER_H
#define UIMAPCONTROLLER_H
#include "qqmlcomponent.h"
#include "qquickitem.h"
#include <QQmlApplicationEngine>
#include "QObject"

#include "cellcontroller.h"
#include "markercontroller.h"
#include "Enums/mapsettings.h"


class UIMapController: public QObject
{
	Q_OBJECT
public:
	void init();
	void registerComponent();

	Q_INVOKABLE CellController* getCCntr();
	Q_INVOKABLE MarkerController * getMarkerContr();
	Q_INVOKABLE void setFocus(int id);

	void setEngine(QQmlApplicationEngine* engine);
	static UIMapController* getInstance();
	CellController* getCCntrByCor(int x, int y);

public slots:
	void startGame();

signals:
	void focusChanged(int x, int y);

protected:

	void InitCells();
	void InitMarker();

	static UIMapController* s_instance;

	UIMapController(QObject* parent = nullptr);
	QQmlApplicationEngine* m_engine;

	QQuickItem* m_cellUIObj[MAP_WIDTH][MAP_HEIGHT];

	CellController* m_cellCntrs[MAP_WIDTH][MAP_HEIGHT];

	int m_cnt;
	int m_boarderWidth;

	MarkerController * m_markerCntr;


	//support members for creating and linking cell objects
	int m_i;
	int m_j;
};

#endif // UIMAPCONTROLLER_H
