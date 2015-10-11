#ifndef UNITWRAPPER_H
#define UNITWRAPPER_H
#include "Core/gobjwrapper.h"

class UnitWrapper: public GObjWrapper
{
	Q_OBJECT
public:
	UnitWrapper(QObject* parent = nullptr);
	void setDirection(int direction);
	void setPosition(int x, int y);

	void setSectorType(OBJECT_TYPE type)	{ Q_UNUSED(type); }
signals:
	void directionChanged(int direction);
	void posChanged(int x, int y);

};

#endif // UNITWRAPPER_H
