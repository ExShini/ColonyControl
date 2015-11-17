#ifndef GOALGORITHMS_H
#define GOALGORITHMS_H
#include "Enums/objects.h"

class GObject;

class GOAlgorithms
{
public:
	static int transferResourceByRequest(GObject* sender, GObject* receiver, RESOURSES resType);

private:
	GOAlgorithms();
};

#endif // GOALGORITHMS_H
