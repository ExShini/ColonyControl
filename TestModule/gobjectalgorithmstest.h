#ifndef GOBJECTALGORITHMSTEST_H
#define GOBJECTALGORITHMSTEST_H
#include "Core/gobject.h"
#include "testcase.h"

// test object
class TestGObject: public GObject
{
public:
	TestGObject(GObjWrapper* wrapper = nullptr);
	void addResourseToMap(Resourse* res);
};


// test case
class GObjectAlgorithmsTest: public TestCase
{
public:
	GObjectAlgorithmsTest();
	virtual void executeTest(int testNumber);

protected:
	bool executeT1();
	bool executeT2();
	bool executeT3();
	bool executeT4();
	bool executeT5();


};

#endif // GOBJECTALGORITHMSTEST_H
