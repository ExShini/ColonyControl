#ifndef AROIPLAYER_H
#define AROIPLAYER_H
#include "../player.h"
#include "Core/UnitController/Units/Aroi/aroiunitfactory.h"
#include "Core/buildings/Aroi/aroibuildingfactory.h"

class AroiPlayer: public Player
{
public:
	AroiPlayer(int ID);
	virtual ~AroiPlayer();

	virtual void init();

protected:
	void setAllAroiLimits();
	void setupAroiResPrototypes();
	void prepareAroiResPrototypes();
	void setBuildingPrototypes();

	AroiUnitFactory* m_unitFactory;
	AroiBuildingFactory* m_buildingFactory;


	// human prototypes
	Resourse* m_supplyProtoRes;
	Resourse* m_populationProtoRes;
	Resourse* m_transportShuttle;
	Resourse* m_infrastructure[MAX_LEVEL];


};

#endif // AROIPLAYER_H
