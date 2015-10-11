#include "monitorpanelcontroller.h"
#include "qdebug.h"
#include "Enums/objects.h"
#include "Enums/guisettings.h"
#include "QtQml"

MonitorPanelController* MonitorPanelController::s_instance = nullptr;

/************************************************
 * Func: MonitorPanelController(QObject *parent)
 * Desc: Constructor
 ***********************************************/
MonitorPanelController::MonitorPanelController(QObject *parent) :
	QObject(parent),
	m_engine(nullptr),
	m_mainRaceResource(0),
	m_sciense(0),
	m_mineralWealth(0),
	m_fertility(0),
	m_visible(false),
	m_mainResName(),
	m_scienseName(),
	m_res1Name(),
	m_res2Name(),
	m_res3Name(),
	m_res4Name(),
	m_res1Value(0),
	m_res2Value(0),
	m_res3Value(0),
	m_res4Value(0),
	m_res1Percent(0),
	m_res2Percent(0),
	m_res3Percent(0),
	m_res4Percent(0)
{

}

/************************************************
 * Func: ~MonitorPanelController
 * Desc: Destructor
 ***********************************************/
MonitorPanelController::~MonitorPanelController()
{

}

/************************************************
 * Func: getInstance
 * Desc: singliton implementation
 ***********************************************/
MonitorPanelController* MonitorPanelController::getInstance()
{
	if(s_instance == nullptr)
	{
		s_instance = new MonitorPanelController();
	}

	return s_instance;
}

/************************************************
 * Func: setSecFertility
 * Desc: setup value of sector fertility
 ***********************************************/
void MonitorPanelController::setSecFertility(int fertility)
{
	m_fertility = fertility;
	emit fertilityChanged();
}

/************************************************
 * Func: setSecMineralWealth
 * Desc: setup value of sector mineral wealth
 ***********************************************/
void MonitorPanelController::setSecMineralWealth(int wealth)
{
	m_mineralWealth = wealth;
	emit mineralWealthChanged();
}

/************************************************
 * Func: mineralWealth
 * Desc: return value of sector mineral wealth
 ***********************************************/
int MonitorPanelController::mineralWealth()
{
	return m_mineralWealth;
}

/************************************************
 * Func: fertility
 * Desc: return value of sector fertility
 ***********************************************/
int MonitorPanelController::fertility()
{
	return m_fertility;
}

/************************************************
 * Func: setEngine
 * Desc: setup QQmlApplicationEngine for MonitorPanelController
 ***********************************************/
void MonitorPanelController::setEngine(QQmlApplicationEngine *engine)
{
	m_engine = engine;
}

/************************************************
 * Func: init
 * Desc: initialize staff for MonitorPanelController
 ***********************************************/
void MonitorPanelController::init()
{
	//if engine is null - ERROR!
	if(m_engine == nullptr)
	{
		qDebug() << "MonitorPanelController::init: Engine doesn't set!";
		return;
	}

	m_engine->rootContext()->setContextProperty("MonitorPanelCtr", this);
}

/************************************************
 * Func: resourceChanged
 * Desc: handle change of resourses
 ***********************************************/
void MonitorPanelController::resourceChanged(int type, int value, int maxValue, int number)
{
	switch (type) {
	case FERTILITY:
	{
		setSecFertility(value);
	}
		break;
	case MINERAL_WEALTH:
	{
		setSecMineralWealth(value);
	}
		break;
	default:
	{
		// process products

		if(number == -1)
		{
			qDebug() << "MonitorPanelController::resourceChanged : Uncknown type of resouses!";
			return;
		}

		if(type == NO_RES)
		{
			value = 0;
		}

		QString name = getProductName(type);
		setProduct(number, name, value, maxValue);
	}

		break;
	}
}

/************************************************
 * Func: setVisibility
 * Desc: setup visibility for MonitorPanel
 ***********************************************/
void MonitorPanelController::setVisibility(bool visibility)
{
	m_visible = visibility;
	emit visibilityChanged();
}

/************************************************
 * Func: visibility
 * Desc: return visibility for MonitorPanel
 ***********************************************/
bool MonitorPanelController::visibility()
{
	return m_visible;
}

/************************************************
 * Func: showElent
 * Desc: show MonitorPanel at screen
 ***********************************************/
void MonitorPanelController::showElent()
{
	setVisibility(true);
}

/************************************************
 * Func: getProductName
 * Desc: return resourse name by type
 ***********************************************/
QString MonitorPanelController::getProductName(int type)
{
	QString name("");

	switch (type) {
	case POPULATION:
		name = "Population";
		break;
	case MINERALS:
		name = "Minerals";
		break;
	case INFROSTRUCTURE:
		name = "Infrostructure";
		break;
	case SUPPLY:
		name = "Supply";
		break;
	case SHIPS:
		name = "Ships";
		break;
	case MAIN_RESOURSE:
		name = "Race Resourse";
		break;
	case NO_RES:
		name = "";
		break;
	default:
		qDebug() << "MonitorPanelController::getProductName: Unknown type of product!";
		break;
	}

	return name;
}

/************************************************
 * Func: setProduct
 * Desc: setup product to screen
 ***********************************************/
void MonitorPanelController::setProduct(int resNum, QString name, int value, int maxValue)
{
	if(resNum >= MAX_RES_IN_ONE_SECTOR)
	{
		qDebug() << "MonitorPanelController::setResName: incorrect res number " << resNum;
	}

	//qDebug() << "setProduct resNum" << resNum << " val " << value << " max " << maxValue << " num " << resNum;

	if(maxValue == 0)
		maxValue++;

	int percent = (value * 100) / maxValue;
	if(percent > 100)
		percent = 100;

	switch (resNum)
	{
	case SCIENSE_POSITION:
	{
		m_scienseName = name;
		m_sciense = value;
		emit scienseNameChanged();
		emit scienseValueChanged();
	}
		break;
	case MAIN_RACE_RES_POSITION:
	{
		m_mainResName = name;
		m_mainRaceResource = value;
		emit mainResNameChanged();
		emit mainResValueChanged();
	}
		break;
	case 0:
	{
		m_res1Name = name;
		m_res1Value = value;
		m_res1Percent = percent;
		emit res1Changed();
	}
		break;
	case 1:
	{
		m_res2Name = name;
		m_res2Value = value;
		m_res2Percent = percent;
		emit res2Changed();
	}
		break;
	case 2:
	{
		m_res3Name = name;
		m_res3Value = value;
		m_res3Percent = percent;
		emit res3Changed();
	}
		break;
	case 3:
	{
		m_res4Name = name;
		m_res4Value = value;
		m_res4Percent = percent;
		emit res4Changed();
	}
		break;
	default:
		qDebug() << "MonitorPanelController::setResName: 2 step : incorrect res number " << resNum;
		break;
	}


}
