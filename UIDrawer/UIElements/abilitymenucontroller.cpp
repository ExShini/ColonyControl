#include "abilitymenucontroller.h"
#include "qqmlcontext.h"
#include "qdebug.h"

#include "Enums/guisettings.h"
#include "Enums/procsettings/ability.h"
#include "UIDrawer/UIElements/uiresdictionary.h"
#include "Core/playercontroller.h"
#include "uimapcontroller.h"

AbilityMenuController* AbilityMenuController::s_instance = nullptr;

AbilityMenuController::AbilityMenuController(QObject *parent) :
	QObject(parent),
	m_abilityCreator(nullptr),
	m_buildPanel(nullptr),
	m_abilityCnt(0),
	m_markerCntr(nullptr),
	m_registredAbility()
{
	for(int i = 0; i < MAX_NUMBER_OF_ABILITY_BUTTONS; i++)
	{
		m_abilityButtons[i] = new	AbilityButtonCntr();
	}
}

void AbilityMenuController::setEngine(QQmlApplicationEngine *engine)
{
	m_engine = engine;
}

AbilityMenuController* AbilityMenuController::getInstance()
{
	if(s_instance == nullptr)
	{
		s_instance = new AbilityMenuController();
	}

	return s_instance;
}

void AbilityMenuController::init()
{
	if(m_engine == nullptr)
	{
		qDebug() << "AbilityMenuController::init : Error! m_engine is null!";
		return;
	}

	m_abilityCreator = new QQmlComponent(m_engine
										 , QUrl(QStringLiteral("qrc:/res/BuildCell.qml")));

	if(m_abilityCreator->status() == QQmlComponent::Error)
	{
		qDebug() << "AbilityMenuController::init : Error: " << m_abilityCreator->errorString();
	}


	QList<QObject*> list = m_engine->rootObjects();


	QObject* buildPanelObj = list[0]->findChild<QObject*>("buildPanel");
	m_buildPanel = qobject_cast<QQuickItem*>(buildPanelObj);

	m_markerCntr = UIMapController::getInstance()->getMarkerContr();


	addAbility(UPDATE_BUILDING, (int)t_HUMAN_TRANSPORT_CENTER, 3000, AbilityButtonCntr::ACTIVE_STATE);
	addAbility(ABILITY, (int)ION_CANON, 5000, AbilityButtonCntr::ACTIVE_STATE);
}

void AbilityMenuController::registerComponent()
{
	m_engine->rootContext()->setContextProperty("AbilityMenuCntr", this);

	AbilityButtonCntr::regisrerTypes();
}

void AbilityMenuController::abilityActived(int type, int subType)
{
	QString src = UIResDictionary::getInstance()->getAbilityMouseSrc((ABILITY_TYPE)type, subType);
	m_markerCntr->setAbilityMarkerSrc(src);
}


void AbilityMenuController::sectorChoosed()
{
	int x = m_markerCntr->mapX();
	int y = m_markerCntr->mapY();
	emit tryApplyAbility(x, y, MAIN_PLAYER_ID);
}

void AbilityMenuController::resetMarker()
{
	m_markerCntr->setAbilityMarkerSrc("");
	emit resetAbility();
}

int AbilityMenuController::addAbility(ABILITY_TYPE type, int subType, int defCost, AbilityButtonCntr::ABILITY_STATE state)
{
	if(m_abilityCnt < MAX_NUMBER_OF_ABILITY_BUTTONS)
	{
		AbilityButtonCntr* abilityCntr = m_abilityButtons[m_abilityCnt];

		abilityCntr->setType(type);
		abilityCntr->setSubType(subType);\

		QString iconSrc = UIResDictionary::getInstance()->getAbilityIcon(type, subType);

		abilityCntr->setSrc(iconSrc);
		abilityCntr->setCost(defCost);
		abilityCntr->setstate(state);

		PlayerController* plCntr = PlayerController::getInstance();
		QObject::connect(abilityCntr, SIGNAL(pressedSignal(int,int,int)),
						 plCntr, SLOT(activateAbility(int,int,int)));

		// create qml element

		QObject *object = m_abilityCreator->create();
		QQuickItem * item = qobject_cast<QQuickItem*>(object);

		item->setProperty("cellWidth", ABILITY_BUTTON_SIZE);
		item->setY(ABILITY_BUTTON_SIZE * m_abilityCnt);

		item->setParentItem(m_buildPanel);

		// register ability in map
		int abilityKey = GET_ABILITY_KEY(type, subType);
		if(!m_registredAbility.keys().contains(abilityKey))
		{
			m_registredAbility[abilityKey] = abilityCntr;
		}
		else
		{
			qDebug() << "AbilityMenuController::addAbility: Error! Try to add"
						" ability, witch already exist! type: " << type << " subtype: " << subType;
		}


		m_abilityCnt++;
		return m_abilityCnt - 1;
	}
	else
	{
		qDebug() << "AbilityMenuController::addAbility : Error! we have not more AbilityButtonCntr";
	}

	return INVALIDE_VALUE;
}

AbilityButtonCntr* AbilityMenuController::getAbilityCntr()
{
	if(m_abilityCnt >= 0 && m_abilityCnt < MAX_NUMBER_OF_ABILITY_BUTTONS)
	{
		return m_abilityButtons[m_abilityCnt];
	}
	else
	{
		qDebug() << "AbilityMenuController::getAbilityCntr : Error! something wrong. m_abilityCnt: " << m_abilityCnt;
	}

	return nullptr;
}

void AbilityMenuController::setAbilityCost(ABILITY_TYPE type, int subType, int cost)
{
	int key = GET_ABILITY_KEY(type, subType);
	if(m_registredAbility.keys().contains(key))
	{
		AbilityButtonCntr* cntr = m_registredAbility[key];

		if(cntr == nullptr)
		{
			qDebug() << "AbilityMenuController::setAbilityCost: Error! cntr is null!";
			return;
		}

		cntr->setCost(cost);
	}
	else
	{
		qDebug() << "AbilityMenuController::setAbilityCost: Error! We have-not such ability: type: " << type << " subType: " << subType;
	}
}
