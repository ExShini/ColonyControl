#ifndef UIUNITCONTROLLER_H
#define UIUNITCONTROLLER_H
#include "UIDrawer/UIElements/uiunitcntr.h"
#include "Enums/guisettings.h"

#include "qqmlcomponent.h"
#include "qquickitem.h"
#include <QQmlApplicationEngine>
#include "QObject"

class UiUnitController : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE UiUnitCntr* getUnitCntr();

	void init();

	void setEngine(QQmlApplicationEngine* engine);
	void registerComponent();
	static UiUnitController* getInstance();
	UiUnitCntr* getUnitCntr(int id);

private:
	explicit UiUnitController(QObject *parent = 0);
	~UiUnitController();
	void initUIUnitElements();

	static UiUnitController* s_instance;
	QQmlApplicationEngine* m_engine;

	UiUnitCntr* m_unitControllers[MAX_NUMBER_OF_UNITS];
	QQuickItem* m_unitUIObj[MAX_NUMBER_OF_UNITS];
	int m_unitId;
};

#endif // UIUNITCONTROLLER_H
