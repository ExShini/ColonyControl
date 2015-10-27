#ifndef CELLCONTROLLER_H
#define CELLCONTROLLER_H
#include <QObject>
#include "Enums/objects.h"

//Controller of cell
class CellController : public QObject
{
    Q_OBJECT

    //QML properties
    //animation data
    Q_PROPERTY(bool objIsActive READ isActive NOTIFY isActiveChanged)
    Q_PROPERTY(bool objIsvisible READ objIsvisible NOTIFY objIsvisibleChanged)
	Q_PROPERTY(int id READ id NOTIFY idChanged)

    Q_PROPERTY(QString animMainSrc READ mainObjAnimSrc NOTIFY animChanged)
	Q_PROPERTY(QString backgroundSrc READ backgroundSrc NOTIFY backChanged)
	Q_PROPERTY(QString markerSrc READ markerSrc NOTIFY markerChanged)
    Q_PROPERTY(int animFrameCnt READ mainObjAnimFrameCnt NOTIFY animChanged)
    Q_PROPERTY(double animFrameRate READ mainObjAnimFrameRate NOTIFY animChanged)
	Q_PROPERTY(int rowInFrame READ rowInFrame NOTIFY animChanged)

public:
	explicit CellController(int id = 0, QObject *parent = 0);
    ~CellController();


    //getters for QML
    bool isActive();
    bool objIsvisible();
    QString mainObjAnimSrc();
	QString backgroundSrc();
	QString markerSrc();
    int mainObjAnimFrameCnt();
    double mainObjAnimFrameRate();
	int rowInFrame();
	int id();






signals:
    //signals for QML notification
    void isActiveChanged();
    void objIsvisibleChanged();
    void animChanged();
	void backChanged();
	void markerChanged();
	void mineralWealthChanged();
	void fertilityChanged();
	void idChanged();

public slots:
	void setLevel(int level, int state);
    void setType(int type);
	void setState(int state);

	void setNewAnimation(QString src, int cnt, double rate, int row);
	void setNewBackground(QString src);
	void setPlayerMarker(int playerID);
    void disableObj();
    void enableObj();

	void setSecType(int type);

private:
	int m_id;
    bool m_active;
    bool m_visible;
	int m_state;
	int m_level;
    OBJECT_TYPE m_curType;

    QString m_animSrc;
	QString m_backSrc;
	QString m_markerSrc;
    int m_animFrameCnt;
    double m_animFrameRate;
	int m_rowInFrame;

	int m_fertility;
	int m_mineralWealth;
};

#endif // CELLCONTROLLER_H
