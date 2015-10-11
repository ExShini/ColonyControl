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
	HumanUnitFactory* m_unitFactory;
	HumanBuildingFactory* m_buildingFactory;


};

#endif // HUMANPLAYER_H
