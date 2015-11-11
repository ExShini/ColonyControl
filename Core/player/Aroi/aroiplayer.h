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
	void setupAroiResPrototypes();
	void setAroiResDefValue();

	AroiUnitFactory* m_unitFactory;
	AroiBuildingFactory* m_buildingFactory;

};

#endif // AROIPLAYER_H
