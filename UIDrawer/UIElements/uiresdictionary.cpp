#include "uiresdictionary.h"
#include "Enums/procsettings/ability.h"
#include "Enums/uistate.h"
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
			m_resoursesPath[type][level].path = QString("");
        }
    }

	for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		m_markers[i] = QString("");
	}

	/*********************************
	 *			Buildings
	 ********************************/
	UIResSpecifier* classicNormalSpec = new UIResSpecifier();
	classicNormalSpec->frameCnt = 8;
	classicNormalSpec->rowNumber = 0;
	UIResSpecifier* classicBuildSpec = new UIResSpecifier();
	classicBuildSpec->frameCnt = 4;
	classicBuildSpec->rowNumber = 1;
	UIResSpecifier* classicDestrSpec = new UIResSpecifier();
	classicDestrSpec->frameCnt = 8;
	classicDestrSpec->rowNumber = 0;	// TODO: temprory solution


	// HUMAN
	// t_HUMAN_SETTLERS

	registerResPath(t_HUMAN_SETTLERS, 0, "/img/humanSettlerL1.png");
	addSpecific(t_HUMAN_SETTLERS, 0, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 0, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 0, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 1, "/img/humanSettlerL1.png");
	addSpecific(t_HUMAN_SETTLERS, 1, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 1, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 1, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 2, "/img/humanSettlerL2.png");
	addSpecific(t_HUMAN_SETTLERS, 2, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 2, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 2, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 3, "/img/humanSettlerL3.png");
	addSpecific(t_HUMAN_SETTLERS, 3, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 3, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 3, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 4, "/img/humanSettlerL4.png");
	addSpecific(t_HUMAN_SETTLERS, 4, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 4, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 4, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 5, "/img/humanSettlerL4.png");
	addSpecific(t_HUMAN_SETTLERS, 5, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 5, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 5, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 6, "/img/humanSettlerL4.png");
	addSpecific(t_HUMAN_SETTLERS, 6, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 6, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 6, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 7, "/img/humanSettlerL4.png");
	addSpecific(t_HUMAN_SETTLERS, 7, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 7, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 7, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 8, "/img/humanSettlerL4.png");
	addSpecific(t_HUMAN_SETTLERS, 8, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 8, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 8, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 9, "/img/humanSettlerL4.png");
	addSpecific(t_HUMAN_SETTLERS, 9, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 9, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 9, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_SETTLERS, 10, "/img/humanSettlerL4.png");
	addSpecific(t_HUMAN_SETTLERS, 10, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_SETTLERS, 10, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_SETTLERS, 10, UI_DESTROYED, classicDestrSpec);

	// t_HUMAN_COLONY_CENTER

	classicNormalSpec->frameCnt = 24;
	classicBuildSpec->frameCnt = 24;
	classicDestrSpec->frameCnt = 24;
	registerResPath(t_HUMAN_COLONY_CENTER, 0, "/img/humanColonyCenterL0.png");
	addSpecific(t_HUMAN_COLONY_CENTER, 0, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_COLONY_CENTER, 0, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_COLONY_CENTER, 0, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_COLONY_CENTER, 1, "/img/humanColonyCenterL0.png");
	addSpecific(t_HUMAN_COLONY_CENTER, 1, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_COLONY_CENTER, 1, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_COLONY_CENTER, 1, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_COLONY_CENTER, 2, "/img/humanColonyCenterL0.png");
	addSpecific(t_HUMAN_COLONY_CENTER, 2, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_COLONY_CENTER, 2, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_COLONY_CENTER, 2, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_COLONY_CENTER, 3, "/img/humanColonyCenterL0.png");
	addSpecific(t_HUMAN_COLONY_CENTER, 3, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_COLONY_CENTER, 3, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_COLONY_CENTER, 3, UI_DESTROYED, classicDestrSpec);

	// t_HUMAN_TRANSPORT_CENTER

	classicNormalSpec->frameCnt = 8;
	classicBuildSpec->frameCnt = 8;
	classicDestrSpec->frameCnt = 8;
	registerResPath(t_HUMAN_TRANSPORT_CENTER, 0, "/img/humanTransportCenterL0.png");
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 0, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 0, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 0, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_TRANSPORT_CENTER, 1, "/img/humanTransportCenterL1.png");
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 1, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 1, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 1, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_HUMAN_TRANSPORT_CENTER, 2, "/img/humanTransportCenterL2.png");
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 2, UI_NORMAL, classicNormalSpec);
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 2, UI_BUILDED, classicBuildSpec);
	addSpecific(t_HUMAN_TRANSPORT_CENTER, 2, UI_DESTROYED, classicDestrSpec);

	// AROI
	// t_AROI_HIVE

	registerResPath(t_AROI_HIVE, 0, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 0, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 0, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 0, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 1, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 1, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 1, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 1, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 2, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 2, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 2, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 2, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 3, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 3, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 3, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 3, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 4, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 4, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 4, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 4, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 5, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 5, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 5, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 5, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 6, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 6, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 6, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 6, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 7, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 7, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 7, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 7, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 8, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 8, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 8, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 8, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 9, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 9, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 9, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 9, UI_DESTROYED, classicDestrSpec);

	registerResPath(t_AROI_HIVE, 10, "/img/aroiHiveL1.png");
	addSpecific(t_AROI_HIVE, 10, UI_NORMAL, classicNormalSpec);
	addSpecific(t_AROI_HIVE, 10, UI_BUILDED, classicBuildSpec);
	addSpecific(t_AROI_HIVE, 10, UI_DESTROYED, classicDestrSpec);

	/*********************************
	 *			Units
	 ********************************/

	// HUMAN

	registerResPath(t_HUMAN_SHUTTLE, 0, "/img/PionerL0.png");
	addSpecific(t_HUMAN_SHUTTLE, 0, UI_NORMAL, classicNormalSpec);

	registerResPath(t_HUMAN_ION_CANON_SATELLITE, 0, "/img/IonCanonAbility.png");
	addSpecific(t_HUMAN_ION_CANON_SATELLITE, 0, UI_NORMAL, classicNormalSpec);

	registerResPath(t_HUMAN_ION_CANON_BULLET, 0, "/img/IonCanonBullet.png");
	addSpecific(t_HUMAN_ION_CANON_BULLET, 0, UI_NORMAL, classicNormalSpec);


	/*********************************
	 *			Other
	 ********************************/

	registerResPath(t_MOUNT, 0, "/img/LavaMount_1.png", true);
	addSpecific(t_MOUNT, 0, UI_NORMAL, classicNormalSpec);

	registerResPath(t_FERTILYTY_FIELD, 0, "/img/NGround_1B.png", true);
	addSpecific(t_FERTILYTY_FIELD, 0, UI_NORMAL, classicNormalSpec);

	registerResPath(t_DESERT, 0, "/img/Desert.png", true);
	addSpecific(t_DESERT, 0, UI_NORMAL, classicNormalSpec);

	registerResPath(t_MINERAL_FIELD, 0, "/img/MineralField.png", true);
	addSpecific(t_MINERAL_FIELD, 0, UI_NORMAL, classicNormalSpec);

	registerResPath(t_LAVA, 0, "/img/LavaField.png", true);
	addSpecific(t_LAVA, 0, UI_NORMAL, classicNormalSpec);

	registerResPath(t_DEEP_LAVA, 0, "/img/DeepLava.png", true);
	addSpecific(t_DEEP_LAVA, 0, UI_NORMAL, classicNormalSpec);


	registerMarkerPath(Human, 0, "/img/HumMarker_Blue.png");
	registerMarkerPath(Human, 1, "/img/HumMarker_Red.png");

	registerMarkerPath(Aroi, 0, "/img/HumMarker_Blue.png");
	registerMarkerPath(Aroi, 1, "/img/HumMarker_Red.png");


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
QString UIResDictionary::getResource(int type, int level, int state, int& row, int& frameCnt)
{
    if(type == INVALID_OBJ_TYPE)
        return QString("");

	QString path = m_resoursesPath[type][level].path;

    if(path.isEmpty())
    {
        qDebug() << "IResDictionary::getResource: ERROR! empty path!";
		return "";
    }

	UIResourse& uiRes = m_resoursesPath[type][level];

	if(!uiRes.spec.keys().contains(state))
	{
		qDebug() << "IResDictionary::getResource: ERROR! uiRes.spec.keys does not contain this state: !" << state;
		row = INVALIDE_VALUE;
		frameCnt = INVALIDE_VALUE;
		return "";
	}

	UIResSpecifier* spec = uiRes.spec[state];

	if(spec == nullptr)
	{
		qDebug() << "IResDictionary::getResource: ERROR! spec is null!";
		row = INVALIDE_VALUE;
		frameCnt = INVALIDE_VALUE;
		return "";
	}

	row = spec->rowNumber;
	frameCnt = spec->frameCnt;

    return path;
}

/************************************************
 * Func: registerResPath
 * Desc: Add new resorse path to dictionary.
 ***********************************************/
void UIResDictionary::registerResPath(int type, int level, QString path, bool random)
{
	m_resoursesPath[type][level].path = path;
}

/************************************************
 * Func: addSpecific
 * Desc: Add new specifier to dictionary.
 ***********************************************/
void UIResDictionary::addSpecific(int type, int level, int state, UIResSpecifier *spec)
{
	UIResourse& res = m_resoursesPath[type][level];

	if(spec == nullptr)
	{
		qDebug() << "UIResDictionary::addSpecific: Error!!! spec is null for type " << type << " level: " << level << " state: " << state;
		return;
	}

	if(res.spec.keys().contains(state))
	{
		qDebug() << "UIResDictionary::addSpecific: Error!!! already have Specific for type: " << type << " level: " << level << " state: " << state;
	}

	UIResSpecifier* resSpec = new UIResSpecifier();
	memcpy(resSpec, spec, sizeof(UIResSpecifier));

	res.spec[state] = resSpec;
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
