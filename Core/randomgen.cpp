#include "randomgen.h"
#include <time.h>
#include <stdlib.h>
#include "qglobal.h"



static RanContainer * randomTable = nullptr;
static short randomConter = 0;

/************************************************
 * Func: RandomGen
 * Desc: constructor
 * Note: it never used
 ***********************************************/
RandomGen::RandomGen()
{
}

/************************************************
 * Func: init
 * Desc: Initialize random generator
 ***********************************************/
void RandomGen::init()
{
	int randValue = 0;

    time_t td;
    td = time(NULL);


	int seed = td % MAX_RAND_NUM;
	qsrand(seed);

	randomTable = new RanContainer();
    if ( randomTable != NULL )
    {
        for (int i = 0; i < RAND_BUFF_LENGTH; i++)
        {
			randValue = qrand() % MAX_RAND_NUM;
			randomTable->RandTable[i] = randValue;
        }
    }
}

/************************************************
 * Func: getRand
 * Desc: return random generated value
 ***********************************************/
int RandomGen::getRand()
{
	int ret;

	ret = randomTable->RandTable[randomConter];
    randomConter++;
    if (randomConter >= RAND_BUFF_LENGTH)
    {
        randomConter = 0;
    }
    return ret;
}
