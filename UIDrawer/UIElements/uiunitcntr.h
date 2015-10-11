#ifndef UIUNITCNTR_H
#define UIUNITCNTR_H

#include "Enums/objects.h"
#include <QObject>

class UiUnitCntr: public QObject
{
	Q_OBJECT

	//QML properties
	//animation data
	Q_PROPERTY(bool objIsActive READ isActive NOTIFY isActiveChanged)
	Q_PROPERTY(bool objIsvisible READ objIsvisible NOTIFY objIsvisibleChanged)
	Q_PROPERTY(int id READ id NOTIFY idChanged)

	Q_PROPERTY(QString animMainSrc READ animSrc NOTIFY animChanged)
	Q_PROPERTY(int animFrameCnt READ animFrameCnt NOTIFY animChanged)
	Q_PROPERTY(double animFrameRate READ animFrameRate NOTIFY animChanged)
	Q_PROPERTY(int direction READ direction NOTIFY directionChanged)
	Q_PROPERTY(int xPos READ xPos NOTIFY posChanged)
	Q_PROPERTY(int yPos READ yPos NOTIFY posChanged)

public:
	UiUnitCntr(int id = 0, QObject *parent = nullptr);
	~UiUnitCntr();

	bool isActive();
	bool objIsvisible();
	QString animSrc();
	int animFrameCnt();
	double animFrameRate();
	int id();
	int xPos();
	int yPos();
	int direction();


signals:
	//signals for QML notification
	void isActiveChanged();
	void objIsvisibleChanged();
	void animChanged();
	void idChanged();
	void posChanged();
	void directionChanged();

public slots:
	void setLevel(int level);
	void setType(int type);

	void setNewAnimation(QString src, int cnt, double rate);
	void disableObj();
	void enableObj();

	void setPosition(int x, int y);
	void setDirection(int direction);

private:
	int m_id;
	bool m_active;
	bool m_visible;
	OBJECT_TYPE m_curType;

	QString m_animSrc;
	int m_animFrameCnt;
	double m_animFrameRate;

	int m_xPos;
	int m_yPos;
	int m_direction;
};

#endif // UIUNITCNTR_H
