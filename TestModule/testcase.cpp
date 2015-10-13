#include "testcase.h"
#include "qdebug.h"

TestCase::TestCase(QString name):
	m_name(name)
{

}

void TestCase::executeTest(int testNumber)
{
	QString message = "Test Case: " + m_name + " test #" + QString::number(testNumber);
	qDebug() << message;
}
