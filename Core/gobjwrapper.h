#ifndef GOBJWRAPPER_H
#define GOBJWRAPPER_H

#include "Enums/objects.h"
#include "Enums/mapsettings.h"
#include "Enums/races.h"
#include <QObject>

class GObject;

class GObjWrapper : public QObject
{
    Q_OBJECT
public:
    explicit GObjWrapper(QObject *parent = 0);
    ~GObjWrapper();

    void setType(OBJECT_TYPE type);
    void setLevel(int level);
	void setMarker(int plID);
    void setEnabled();
    void setDisabled();

	//sectors data methods
	virtual void setSectorType(OBJECT_TYPE type);

signals:
    void changeType(int type);
    void changeLevel(int level);
	void changeMarker(int plId);
    void enable();
    void disable();

	void changeSectorType(int type);


public slots:
};

#endif // GOBJWRAPPER_H
