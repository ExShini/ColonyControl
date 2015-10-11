#ifndef UIRESDICTIONARY_H
#define UIRESDICTIONARY_H
#include "QString"
#include "Enums/objects.h"
#include "Enums/gameprocessingsettings.h"
#include "Enums/guisettings.h"
#include <QMap>

class UIResDictionary
{
public:

    static UIResDictionary* getInstance();
    QString getResource(int type, int level);
	QString getMarkerSrc(int playerID);
	QString getAbilityIcon(ABILITY_TYPE type, int subType);
	QString getAbilityMouseSrc(ABILITY_TYPE type, int subType);
	void registerPlayer(Race race, int id);

protected:
	void registerResPath(int type, int level, QString path, bool random = false);
	void registerMarkerPath(Race race, int id, QString path);
	void registerAbilityButtonSrc(int id, QString icon, QString mouseMarker);
	void registerBuildButtonSrc(int id, QString icon, QString mouseMarker);

	UIResDictionary();
	~UIResDictionary();


    static UIResDictionary* s_instance;
    QString m_resoursesPath[NUM_OF_OBJ_TYPES][MAX_LEVEL];
	QString m_markerDictionary[NUM_OF_RACE][NUMBER_OF_PLAYERS];
	QString m_markers[NUMBER_OF_PLAYERS];
	QMap<int, QString> m_abilityButtonIcons;
	QMap<int, QString> m_buildButtonIcons;
	QMap<int, QString> m_mouseMarkerPathBuilding;
	QMap<int, QString> m_mouseMarkerPathAbility;

};

#endif // UIRESDICTIONARY_H
