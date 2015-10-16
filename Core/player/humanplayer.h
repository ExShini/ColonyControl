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
	HumanUnitFactory* m_unitFactory;
	HumanBuildingFactory* m_buildingFactory;


	Resourse* m_supplyPropoRes;
	Resourse* m_populationProtoRes;
	Resourse* m_transportShuttle;


};

#endif // HUMANPLAYER_H
