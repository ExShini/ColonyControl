#ifndef BASEBUILDINGTESTER_H
#define BASEBUILDINGTESTER_H
#include "testcase.h"
#include "Core/buildings/building.h"


class TestBuilding : public Building
{
public:
	TestBuilding();
	void setup1Env();
	void setup2Env();
	void setup3Env();
	void setup4Env();
	void setup5Env();
	void setup6Env();
	void setup7Env();

	void execResProcess();
};

class BaseBuildingTester: public TestCase
{
public:
	BaseBuildingTester();
	virtual void executeTest(int testNumber);

protected:
	bool executeT1();
	bool executeT2();
	bool executeT3();
	bool executeT4();
	bool executeT5();
	bool executeT6();
};

#endif // BASEBUILDINGTESTER_H
