#include "unitwrapper.h"

UnitWrapper::UnitWrapper(QObject *parent):
	GObjWrapper(parent)
{

}

void UnitWrapper::setPosition(int x, int y)
{
	emit posChanged(x, y);
}

void UnitWrapper::setDirection(int direction)
{
	emit directionChanged(direction);
}
