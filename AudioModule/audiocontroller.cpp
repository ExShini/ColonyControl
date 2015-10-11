#include "audiocontroller.h"
#include "Core/randomgen.h"
#include "qdebug.h"
#include "QApplication"

AudioController* AudioController::s_instance = nullptr;


AudioController::AudioController(QObject *parent):
	QObject(parent),
	m_playList()
{
	addTrack("Best_of_Times_Kyle_Gabler");
	addTrack("Atrox_OST-Track_1");
	addTrack("Atrox_OST-Track_2");
	addTrack("Atrox_OST-Track_3");
	addTrack("Atrox_OST-Track_5");
	addTrack("Audiomachine-Devils_Tower");
}

AudioController::~AudioController()
{

}


void AudioController::addTrack(QString name)
{
	QString path = QUrl::fromLocalFile(QApplication::applicationDirPath() +
									   "/music/" + name + ".mp3").toString();
	m_playList.push_back(path);
}

AudioController* AudioController::getInstance()
{
	if(s_instance == nullptr)
	{
		s_instance = new AudioController();
	}

	return s_instance;
}

QString AudioController::getNextTrack()
{
	QString trackSrc = m_playList.front();

	m_playList.pop_front();
	m_playList.push_back(trackSrc);

	return trackSrc;
}

void AudioController::init()
{
	//if engine is null - ERROR!
	if(m_engine == nullptr)
	{
		qDebug() << "UIMapController::init: Engine doesn't set!";
		return;
	}

	m_engine->rootContext()->setContextProperty("AudioController", this);

	// start from random track
	int startShifting = RandomGen::getRand();
	startShifting = startShifting % m_playList.count();

	while (startShifting > 0)
	{
		getNextTrack();
		startShifting--;
	}
}
