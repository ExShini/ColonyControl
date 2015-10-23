#include "testcase.h"
#include "qdebug.h"

TestCase::TestCase(QString name):
	m_name(name)
{

}

void TestCase::executeTest(int testNumber)
{
	qDebug() << "Test Case: " << m_name << " test #" << QString::number(testNumber);
}
