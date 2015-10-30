#ifndef UITIMINGMANAGER_H
#define UITIMINGMANAGER_H

#include "UIElements/cellcontroller.h"

#include <QObject>
#include <QTimer>
#include <qlist.h>

class UITimingManager : public QObject
{
    Q_OBJECT
public:
    static UITimingManager* getInstance();
    void start();
    void addCCCntr(CellController* control);
signals:

public slots:
    void tick();
protected:
    explicit UITimingManager(QObject *parent = 0);
    static UITimingManager* s_instance;

    QTimer* m_timer;
    double m_timeStap;

    bool m_revert;

    QList<CellController*>* m_cellCntrsPingPtr;
    QList<CellController*>* m_cellCntrsPongPtr;

    QList<CellController*> m_cellCntrsPing;
    QList<CellController*> m_cellCntrsPong;
};

#endif // UITIMINGMANAGER_H
