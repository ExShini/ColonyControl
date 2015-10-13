#ifndef REQUESTMANAGERTEST_H
#define REQUESTMANAGERTEST_H
#include "testcase.h"

class RequestManagerTest: public TestCase
{
public:
	RequestManagerTest();
	virtual void executeTest(int testNumber);

protected:
	bool executeT1();
	bool executeT2();
	bool executeT3();
	bool executeT4();
};

#endif // REQUESTMANAGERTEST_H
