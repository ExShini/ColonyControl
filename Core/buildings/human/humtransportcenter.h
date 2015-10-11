#ifndef HUMTRANSPORTCENTER_H
#define HUMTRANSPORTCENTER_H
#include "humcolonycenter.h"

class HumTransportCenter: public HumColonyCenter
{
public:
	HumTransportCenter(GObjWrapper *wrapper, Sector *sector, int population, int initialStep, int plID);
	virtual ~HumTransportCenter();
};

#endif // HUMTRANSPORTCENTER_H
