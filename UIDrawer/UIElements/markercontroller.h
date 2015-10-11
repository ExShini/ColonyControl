#ifndef MARKERCONTROLLER_H
#define MARKERCONTROLLER_H
#include "Enums/mapsettings.h"

#include <QObject>

class MarkerController : public QObject
{
	Q_OBJECT
public:

	Q_PROPERTY(int X READ X NOTIFY XChanged)
	Q_PROPERTY(int Y READ Y NOTIFY YChanged)
	Q_PROPERTY(QString src READ src NOTIFY srcChanged)
	Q_PROPERTY(QString abilityMarker READ abilityMarker NOTIFY abilityMarkerChanged)
	Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)

	int X()	{ return m_x;  }
	int Y()	{ return m_y; }
	int mapX()	{ return GET_MAP_X(m_x); }
	int mapY()	{ return GET_MAP_Y(m_y); }
	QString src()	{ return m_src; }
	QString abilityMarker()	{ return m_abilityMarkerSrc; }
	bool visible()	{ return m_visible; }


	void setX(int value);
	void setY(int value);
	void setSrc(QString src);
	void setAbilityMarkerSrc(QString src);
	void setVisible(bool value);

	explicit MarkerController(QObject *parent = 0);
	~MarkerController();

signals:
	void XChanged();
	void YChanged();
	void srcChanged();
	void abilityMarkerChanged();
	void visibleChanged();

public slots:


private:
	int m_x;
	int m_y;
	QString m_src;
	QString m_abilityMarkerSrc;
	bool m_visible;
};

#endif // MARKERCONTROLLER_H
