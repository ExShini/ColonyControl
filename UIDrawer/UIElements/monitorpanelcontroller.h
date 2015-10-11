#ifndef MONITORPANELCONTROLLER_H
#define MONITORPANELCONTROLLER_H

#include <QQmlApplicationEngine>
#include "qqmlcontext.h"
#include <QObject>
#include "Enums/objects.h"
#include "qdebug.h"

class MonitorPanelController : public QObject
{
	Q_OBJECT
public:
	Q_PROPERTY(int fertility READ fertility NOTIFY fertilityChanged)
	Q_PROPERTY(int mineralWealth READ mineralWealth NOTIFY mineralWealthChanged)
	Q_PROPERTY(bool visibility READ visibility NOTIFY visibilityChanged)

	Q_PROPERTY(QString mainResName READ mainResName NOTIFY mainResNameChanged)
	Q_PROPERTY(QString scienseName READ scienseName NOTIFY scienseNameChanged)

	Q_PROPERTY(int mainResValue READ mainResValue NOTIFY mainResValueChanged)
	Q_PROPERTY(int scienseValue READ scienseValue NOTIFY scienseValueChanged)

	Q_PROPERTY(QString res1Name READ res1Name NOTIFY res1Changed)
	Q_PROPERTY(QString res2Name READ res2Name NOTIFY res2Changed)
	Q_PROPERTY(QString res3Name READ res3Name NOTIFY res3Changed)
	Q_PROPERTY(QString res4Name READ res4Name NOTIFY res4Changed)

	Q_PROPERTY(int res1Percent READ res1Percent NOTIFY res1Changed)
	Q_PROPERTY(int res2Percent READ res2Percent NOTIFY res2Changed)
	Q_PROPERTY(int res3Percent READ res3Percent NOTIFY res3Changed)
	Q_PROPERTY(int res4Percent READ res4Percent NOTIFY res4Changed)

	Q_PROPERTY(int res1Value READ res1Value NOTIFY res1Changed)
	Q_PROPERTY(int res2Value READ res2Value NOTIFY res2Changed)
	Q_PROPERTY(int res3Value READ res3Value NOTIFY res3Changed)
	Q_PROPERTY(int res4Value READ res4Value NOTIFY res4Changed)



	static MonitorPanelController* getInstance();
	void init();

	void setEngine(QQmlApplicationEngine *engine);

	void setSecFertility(int fertility);
	void setSecMineralWealth(int wealth);
	void setVisibility(bool visibility);




	int mineralWealth();
	int fertility();
	bool visibility();

	QString mainResName()	{ return m_mainResName; }
	QString scienseName()	{ return m_scienseName; }

	QString res1Name()	{ return m_res1Name; }
	QString res2Name()	{ return m_res2Name; }
	QString res3Name()	{ return m_res3Name; }
	QString res4Name()	{ return m_res4Name; }

	int mainResValue()	{ return m_mainRaceResource; }
	int scienseValue()	{ return m_sciense; }

	int res1Value()		{ return m_res1Value; }
	int res2Value()		{ return m_res2Value; }
	int res3Value()		{ return m_res3Value; }
	int res4Value()		{ return m_res4Value; }

	int res1Percent()		{ return m_res1Percent; }
	int res2Percent()		{ return m_res2Percent; }
	int res3Percent()		{ return m_res3Percent; }
	int res4Percent()		{ return m_res4Percent; }

public slots:
	void resourceChanged(int type, int value, int maxValue, int number);
	void showElent();

signals:
	void fertilityChanged();
	void mineralWealthChanged();
	void visibilityChanged();

	void mainResNameChanged();
	void scienseNameChanged();

	void mainResValueChanged();
	void scienseValueChanged();

	void res1Changed();
	void res2Changed();
	void res3Changed();
	void res4Changed();

private:
	explicit MonitorPanelController(QObject *parent = 0);
	~MonitorPanelController();

	void setProduct(int resNum, QString name, int value, int maxValue);
	QString getProductName(int type);

	static MonitorPanelController* s_instance;

	QQmlApplicationEngine* m_engine;

	int m_mainRaceResource;
	int m_sciense;
	int m_mineralWealth;
	int m_fertility;
	bool m_visible;

	QString m_mainResName;
	QString m_scienseName;

	QString m_res1Name;
	QString m_res2Name;
	QString m_res3Name;
	QString m_res4Name;

	int m_res1Value;
	int m_res2Value;
	int m_res3Value;
	int m_res4Value;

	int m_res1Percent;
	int m_res2Percent;
	int m_res3Percent;
	int m_res4Percent;
};

#endif // MONITORPANELCONTROLLER_H
