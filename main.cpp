#include "string"
#include "qdebug.h"
#include "gameapp.h"
#include "TestModule/testmanager.h"

/************************************************
 * Func: main
 * Desc: main function
 * All adventures started here :)
 ***********************************************/
int main(int argc, char *argv[])
{

#if QT_DEBUG_OUTPUT
	qDebug() << "QT_DEBUG_OUTPUT.";
#endif

	GameApp* game = new GameApp(argc, argv);
	game->init();

	// put "test" argument for start self testing
	if(argc >= 2)
	{
		if(!strcmp(argv[1], "test"))
		{
			qDebug() << "Testing mode.";
			TestManager testManager;
			testManager.exec();

			return 0;
		}
	}

	game->start();



	return 0;
}
