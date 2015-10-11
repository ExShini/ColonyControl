#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include "Enums/randomsettings.h"

struct RanContainer
{
	int RandTable[RAND_BUFF_LENGTH];
};

class RandomGen
{
public:
	static void init();
	static int getRand();
private:
	RandomGen();

};

#endif // RANDOMGEN_H
