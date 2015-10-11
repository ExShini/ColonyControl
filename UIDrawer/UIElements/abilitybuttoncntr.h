#ifndef ABILITYBUTTONCNTR_H
#define ABILITYBUTTONCNTR_H
#include "Enums/objects.h"
#include "Enums/guisettings.h"
#include "Enums/gameprocessingsettings.h"
#include "QObject"

class AbilityButtonCntr: public QObject
{
	Q_OBJECT
	Q_ENUMS(ABILITY_STATE)

public:

	enum ABILITY_STATE
	{
		INVALIDE_STATE = 0,
		ACTIVE_STATE,
		DISABLE_STATE,
		HIDEN_STATE
	};


	Q_PROPERTY(QString src READ src NOTIFY srcChanged)
	Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
	Q_PROPERTY(int cost READ cost NOTIFY costChanged)
	Q_PROPERTY(ABILITY_STATE state READ state NOTIFY stateChanged)
	Q_INVOKABLE void wasPressed();


	AbilityButtonCntr(ABILITY_TYPE type = INVALIDE_TYPE, int subType = INVALIDE_VALUE, QObject* parent = nullptr);
	virtual ~AbilityButtonCntr();

	static void regisrerTypes();

	QString src()			{ return m_src; }
	QString description()	{ return m_description; }
	int cost()				{ return m_cost; }
	ABILITY_STATE state()	{ return m_state; }


	void setSrc(QString src);
	void setDescription(QString description);
	void setCost(int cost);
	void setstate(ABILITY_STATE state);
	void setType(ABILITY_TYPE type)		{ m_type = type; }
	void setSubType(int subType)		{ m_subType = subType; }


signals:
	void srcChanged();
	void descriptionChanged();
	void costChanged();
	void stateChanged();

	void pressedSignal(int type, int subType, int playerID = MAIN_PLAYER_ID);

protected:
	ABILITY_TYPE m_type;
	int m_subType;		// subType - store type of ability - objectType for buiding or abilityType

	QString m_src;
	QString m_description;
	int m_cost;
	ABILITY_STATE m_state;

};

#endif // ABILITYBUTTONCNTR_H
