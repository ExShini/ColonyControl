#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include "Core/UnitController/Units/Human/humanunitfactory.h"
#include "Core/buildings/human/humanbuildingfactory.h"

class HumanPlayer: public Player
{
public:
	HumanPlayer(int ID);
	virtual ~HumanPlayer();

	virtual void init();

protected:
	void setAllHumanLimits();
	void setupHumanResPrototypes();
	void prepareHumanResPrototypes();
	void setBuildingPrototypes();

	HumanUnitFactory* m_unitFactory;
	HumanBuildingFactory* m_buildingFactory;


	// human prototypes
	Resourse* m_supplyProtoRes;
	Resourse* m_populationProtoRes;
	Resourse* m_transportShuttle;
	Resourse* m_infrastructure[MAX_LEVEL];


};

#endif // HUMANPLAYER_H
