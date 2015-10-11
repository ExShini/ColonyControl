#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H
#include "QObject"
#include "qqmlcomponent.h"
#include <QQmlApplicationEngine>
#include "qqmlcontext.h"

class AudioController: public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE QString getNextTrack();


	static AudioController* getInstance();
	void setEngine(QQmlApplicationEngine *engine)			{ m_engine = engine; }
	void init();
	virtual ~AudioController();

protected:
	AudioController(QObject* parent = nullptr);

	void addTrack(QString name);
	static AudioController* s_instance;
	QQmlApplicationEngine* m_engine;
	QList<QString> m_playList;
};

#endif // AUDIOCONTROLLER_H
