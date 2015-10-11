#include "uiresdictionary.h"
#include "Enums/procsettings/ability.h"
#include "qdebug.h"

UIResDictionary* UIResDictionary::s_instance = nullptr;

/************************************************
 * Func: UIResDictionary()
 * Desc: Constructor.
 ***********************************************/
UIResDictionary::UIResDictionary()
{
    for(int type = 0; type < NUM_OF_OBJ_TYPES; type++)
    {
        for(int level = 0; level < MAX_LEVEL; level++)
        {
            m_resoursesPath[type][level] = QString("");
        }
    }

	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		m_markers[i] = QString("");
	}

	/*********************************
	 *			Buildings
	 ********************************/

	registerResPath(t_HUMAN_SETTLERS, 0, "/img/humanSettlerL0.png");
	registerResPath(t_HUMAN_SETTLERS, 1, "/img/humanSettlerL1.png");
	registerResPath(t_HUMAN_SETTLERS, 2, "/img/humanSettlerL2.png");
	registerResPath(t_HUMAN_SETTLERS, 3, "/img/humanSettlerL3.png");
	registerResPath(t_HUMAN_SETTLERS, 4, "/img/humanSettlerL4.png");

	registerResPath(t_HUMAN_COLONY_CENTER, 0, "/img/humanColonyCenterL0.png");
	registerResPath(t_HUMAN_COLONY_CENTER, 1, "/img/humanColonyCenterL1.png");
	registerResPath(t_HUMAN_COLONY_CENTER, 2, "/img/humanColonyCenterL2.png");
	registerResPath(t_HUMAN_COLONY_CENTER, 3, "/img/humanColonyCenterL2.png");

	registerResPath(t_HUMAN_TRANSPORT_CENTER, 0, "/img/humanTransportCenterL0.png");
	registerResPath(t_HUMAN_TRANSPORT_CENTER, 1, "/img/humanTransportCenterL0.png");
	registerResPath(t_HUMAN_TRANSPORT_CENTER, 2, "/img/humanTransportCenterL0.png");


	/*********************************
	 *			Units
	 ********************************/

	registerResPath(t_HUMAN_SHUTTLE, 0, "/img/PionerL0.png");
	registerResPath(t_HUMAN_ION_CANON_SATELLITE, 0, "/img/IonCanonAbility.png");
	registerResPath(t_HUMAN_ION_CANON_BULLET, 0, "/img/IonCanonBullet.png");


	/*********************************
	 *			Other
	 ********************************/

	registerResPath(t_MOUNT, 0, "/img/LavaMount_1.png", true);
	registerResPath(t_FERTILYTY_FIELD, 0, "/img/NGround_1B.png", true);
	registerResPath(t_DESERT, 0, "/img/Desert.png", true);
	registerResPath(t_MINERAL_FIELD, 0, "/img/MineralField.png", true);
	registerResPath(t_LAVA, 0, "/img/LavaField.png", true);
	registerResPath(t_DEEP_LAVA, 0, "/img/DeepLava.png", true);


	registerMarkerPath(Human, 0, "/img/HumMarker_Blue.png");
	registerMarkerPath(Human, 1, "/img/HumMarker_Red.png");


	registerBuildButtonSrc(t_HUMAN_TRANSPORT_CENTER, "/img/HumTransportCenter_Icon.png", "/img/HumTransportCenter.png");
	registerAbilityButtonSrc(ION_CANON, "/img/KILLLLL.png", "/img/KILLLLL.png");
}


/************************************************
 * Func: getMarkerSrc
 * Desc: Return src for markers.
 ***********************************************/
QString UIResDictionary::getMarkerSrc(int playerID)
{
	if(playerID == INVALIDE_VALUE)
		return QString("");

	QString src = m_markers[playerID];

	if(src.isEmpty())
	{
		qDebug()<< "UIResDictionary::getMarkerSrc : empty marker src!";
	}

	return src;
}

/************************************************
 * Func: getAbilityIcon
 * Desc: Return src for button icon.
 ***********************************************/
QString UIResDictionary::getAbilityIcon(ABILITY_TYPE type, int subType)
{
	QString src = "";

	if(type == UPDATE_BUILDING)
	{
		if(m_buildButtonIcons.keys().contains(subType))
		{
			src = m_buildButtonIcons[subType];
		}
		else
		{
			qDebug() << "UIResDictionary::getAbilityIcon: Error! we have not resource for building icon: " << subType;
		}
	}
	else if(type == ABILITY)
	{
		if(m_abilityButtonIcons.keys().contains(subType))
		{
			src = m_abilityButtonIcons[subType];
		}
		else
		{
			qDebug() << "UIResDictionary::getAbilityIcon: Error! we have not resource for ability icon: " << subType;
		}
	}
	else
	{
		qDebug() << "UIResDictionary::getAbilityIcon: Error! wrong type : " << type;
	}

	return src;
}

/************************************************
 * Func: getAbilityMouseSrc
 * Desc: Return src for ability marker.
 ***********************************************/
QString UIResDictionary::getAbilityMouseSrc(ABILITY_TYPE type, int subType)
{
	QString src = "";

	if(type == UPDATE_BUILDING)
	{
		if(m_mouseMarkerPathBuilding.keys().contains(subType))
		{
			src = m_mouseMarkerPathBuilding[subType];
		}
		else
		{
			qDebug() << "UIResDictionary::getAbilityMouseSrc: Error! we have not resource for building icon: " << subType;
		}
	}
	else if(type == ABILITY)
	{
		if(m_mouseMarkerPathAbility.keys().contains(subType))
		{
			src = m_mouseMarkerPathAbility[subType];
		}
		else
		{
			qDebug() << "UIResDictionary::getAbilityMouseSrc: Error! we have not resource for ability icon: " << subType;
		}
	}
	else
	{
		qDebug() << "UIResDictionary::getAbilityMouseSrc: Error! wrong type : " << type;
	}

	return src;
}


/************************************************
 * Func: ~UIResDictionary
 * Desc: Destructor.
 ***********************************************/
UIResDictionary::~UIResDictionary()
{

}

/************************************************
 * Func: getResource
 * Desc: Return src for images and animations.
 ***********************************************/
QString UIResDictionary::getResource(int type, int level)
{
    if(type == INVALID_OBJ_TYPE)
        return QString("");

    QString path = m_resoursesPath[type][level];

    if(path.isEmpty())
    {
        qDebug() << "IResDictionary::getResource: ERROR! empty path!";
    }

    return path;
}

/************************************************
 * Func: registerResPath
 * Desc: Add new resorse path to dictionary.
 ***********************************************/
void UIResDictionary::registerResPath(int type, int level, QString path, bool random)
{
    m_resoursesPath[type][level] = path;
}

/************************************************
 * Func: registerMarkerPath
 * Desc: Add new resorse path (for markers) to dictionary.
 ***********************************************/
void UIResDictionary::registerMarkerPath(Race race, int id, QString path)
{
	m_markerDictionary[race][id] = path;
}

/************************************************
 * Func: registerAbilityButtonSrc
 * Desc: Add new resorse path (for ability button icon) to dictionary.
 ***********************************************/
void UIResDictionary::registerAbilityButtonSrc(int id, QString icon, QString mouseMarker)
{
	if(!m_abilityButtonIcons.keys().contains(id))
	{
		m_abilityButtonIcons[id] = icon;
		m_mouseMarkerPathAbility[id] = mouseMarker;
	}
	else
	{
		qDebug() << "UIResDictionary::registerAbilityButtonSrc: already have resourse for id: " << id;
	}
}

/************************************************
 * Func: registerBuildButtonSrc
 * Desc: Add new resorse path (for ability button icon) to dictionary.
 ***********************************************/
void UIResDictionary::registerBuildButtonSrc(int id, QString icon, QString mouseMarker)
{
	if(!m_buildButtonIcons.keys().contains(id))
	{
		m_buildButtonIcons[id] = icon;
		m_mouseMarkerPathBuilding[id] = mouseMarker;
	}
	else
	{
		qDebug() << "UIResDictionary::registerBuildButtonSrc: already have resourse for id: " << id;
	}
}


/************************************************
 * Func: registerPlayer
 * Desc: find and setup marker for player
 ***********************************************/
void UIResDictionary::registerPlayer(Race race, int id)
{
	QString src = m_markerDictionary[race][id];
	m_markers[id] = src;
}

/************************************************
 * Func: getInstance
 * Desc: singliton implementation.
 ***********************************************/
UIResDictionary* UIResDictionary::getInstance()
{
    if(s_instance == nullptr)
    {
        s_instance = new UIResDictionary();
    }

    return s_instance;
}
