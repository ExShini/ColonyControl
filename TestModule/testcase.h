#ifndef TESTCASE_H
#define TESTCASE_H
#include "qglobal.h"
#include "QString"

class TestCase
{
public:
	TestCase(QString name);
	virtual void executeTest(int testNumber);
	int getNumOfTests()							{ return m_numOfTests; }
protected:
	int m_numOfTests;
	QString m_name;
};

#endif // TESTCASE_H
