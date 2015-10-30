#include "uitimingmanager.h"

#define ONE_SECOND 1000
#define TIME_STAP 100

UITimingManager* UITimingManager::s_instance = nullptr;

UITimingManager::UITimingManager(QObject *parent) : QObject(parent)
{
    m_timeStap = (double)TIME_STAP / (double)ONE_SECOND;
    m_revert = false;

    m_timer = new QTimer();
    m_timer->setInterval(TIME_STAP);

    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(tick()), Qt::QueuedConnection);

    m_cellCntrsPingPtr = &m_cellCntrsPing;
    m_cellCntrsPongPtr = &m_cellCntrsPong;
}

UITimingManager* UITimingManager::getInstance()
{
    if(s_instance == nullptr)
    {
        s_instance = new UITimingManager(nullptr);
    }

    return s_instance;
}


void UITimingManager::tick()
{
    CellController* cntr = nullptr;

    // process all registred controllers
    while (m_cellCntrsPingPtr->count() > 0)
    {
        cntr = m_cellCntrsPingPtr->front();
        m_cellCntrsPingPtr->pop_front();

        bool toContinue = cntr->elapseTime(m_timeStap);

        if(toContinue)
        {
            m_cellCntrsPongPtr->push_back(cntr);
        }
    }

    // swap buffers
    m_revert = !m_revert;
    if(m_revert)
    {
        m_cellCntrsPingPtr = &m_cellCntrsPong;
        m_cellCntrsPongPtr = &m_cellCntrsPing;
    }
    else
    {
        m_cellCntrsPingPtr = &m_cellCntrsPing;
        m_cellCntrsPongPtr = &m_cellCntrsPong;
    }
}

void UITimingManager::start()
{
    m_timer->start();
}

void UITimingManager::addCCCntr(CellController *control)
{
    m_cellCntrsPongPtr->push_back(control);
}
