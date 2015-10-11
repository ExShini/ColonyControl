#include "humsettlers.h"
#include "qdebug.h"
#include "Enums/objects.h"
#include "Enums/gameprocessingsettings.h"
#include "Core/gobjwrapper.h"


HumSettlers::HumSettlers(GObjWrapper *wrapper, Sector* sector, int population, int initialStep, int plID):
	Building(wrapper, sector, initialStep, plID),
	m_stateCount(0)
{
	m_type = t_HUMAN_SETTLERS;

	m_wrapper->setType(m_type);
	m_wrapper->setLevel(0);
	m_wrapper->setEnabled();

	regResourse(POPULATION,
				m_player->getResLimit(m_type, POPULATION, m_level),
				population,
				false);

	regResourse(SUPPLY,
				m_player->getResLimit(m_type, SUPPLY, m_level),
				50);

	regResourse(INFROSTRUCTURE,
				m_player->getResLimit(m_type, INFROSTRUCTURE, m_level + 1),
				m_player->getResLimit(m_type, INFROSTRUCTURE, m_level));

	m_maxLevel = HUMAN_MAX_SETTLEMENT_LEVEL;
}

HumSettlers::~HumSettlers()
{

}

void HumSettlers::process(int step)
{

	if(step != m_initialStep)
		return;



	int population = getResources(POPULATION);

	int produceFood = HUMANS_GROPS(population * HUMAN_FOOD_PRODUCING) ;
	if (produceFood > m_sector->getFertility())
		produceFood = m_sector->getFertility();

	int food = getResources(SUPPLY);
	food += produceFood;

	//population processing
	int growth = HUMAN_POPULATION_GROWTH(population);
	population +=  growth; //HUMAN_POPULATION_GROWTH(m_population);


	//check limits and consumptions
	//food
	food -= HUMAN_FOOD_CONSUMPTIONS(population);
	if(food < 0)
	{
		population -= HUMAN_HUNGER_DEMAGE(food);
		foodEmigration();
		food = 0;
	}
	else
	{
		//take 12.5% of population and compair it with food storage
		//if food storege will be smoll - emigrate
		int pop125 = population >> 3;
		if(pop125 > food)
		{
			foodEmigration();
		}
	}


	//population
	int populationLimit = getResLimit(POPULATION);
	if(population > populationLimit)
	{
		int excess = population - populationLimit;
		population -= HUMAN_POPULATION_DEMAGE(excess);
		popLimitEmigration();
	}
	else
	{
		//if population less than 75% of population limit and settlement
		//have enough food - send immigrate request
		int pop25Limit = populationLimit >> 2;
		int pop75limit = populationLimit - pop25Limit;

		int immReqValue = pop75limit - population;
		if(immReqValue > 0)
		{
			if(immReqValue > pop25Limit)
			{
				immReqValue = pop25Limit;
			}

			// calculatr num of immigrants with food storage
			int immigrantsWithFood = food / 5;
			if(immReqValue > immigrantsWithFood)
			{
				immReqValue = immigrantsWithFood;
			}

			immigrationReq(immReqValue);

		}
	}


	//infrastructure building
	if(m_level <= m_maxLevel && food > 0)
	{
		int infrostructure = getResources(INFROSTRUCTURE);
		infrostructure += (HUMANS_GROPS(population) / (m_level + 1));
		setResources(INFROSTRUCTURE, infrostructure);
	}



	setResources(POPULATION, population);
	setResources(SUPPLY, food);

	// update main resource
	int mainResChange = HUMANS_GROPS(population);
	m_player->changeMainResValue(mainResChange);


	m_stateCount++;
	if(m_stateCount >= 5)
	{
		checkState();
		m_stateCount = 0;
	}
}

void HumSettlers::immigrationReq(int colonists)
{
	if(colonists <= 0)
	{
		return;
	}

	Request * req = m_requestMap[POPULATION];

	if(req == nullptr)
	{
		req = new Request();
		req->resType = POPULATION;
		req->status = AWAITS;
		req->subject = this;
		req->type = CONSUME;
		req->value = colonists;

		m_requestMap[POPULATION] = req;
	}
	else
	{
		if(req->type == PROVIDE)
		{
			qDebug() << "HumSettlers::immigrationReq: Change req-direction at x:" << getMapX() << " y:" << getMapY();

			// set NOT_ACTUAL for previus request
			req->status = NOT_ACTUAL;
			req->value = 0;

			//create new request
			req = new Request();
			req->resType = POPULATION;
			req->status = AWAITS;
			req->subject = this;
			req->type = CONSUME;
			req->value = colonists;
			m_requestMap[POPULATION] = req;
		}
	}

	if(req->value >= MIN_HUMAN_TO_MOVE && !req->registred)
	{
		m_player->addRequest(req);
	}
}

/*************************************
FUNC: popLimitEmigration()
DESC: Add emigration request (if it needed) and increase number of colonists
*************************************/
void HumSettlers::popLimitEmigration()
{
	int population = getResources(POPULATION);
	int populationLimit = getResLimit(POPULATION);


	Request * req = m_requestMap[POPULATION];

	int col = population - populationLimit;

	// take 25% of population - it is top limit for emigration
	int pop25persent = (population >> 2);

	if(col > pop25persent)
	{
		col = pop25persent;
	}

	if(col > 0)
	{
		if(req == nullptr)
		{
			req = new Request();
			req->resType = POPULATION;
			req->status = AWAITS;
			req->subject = this;
			req->type = PROVIDE;
			req->value = col;

			m_requestMap[POPULATION] = req;
		}

		if(req->type == CONSUME)
		{
			qDebug() << "popLimitEmigration: Change req-direction at x:" << getMapX() << " y:" << getMapY();

			// set NOT_ACTUAL for previus request
			req->status = NOT_ACTUAL;
			req->value = 0;

			//create new request
			req = new Request();
			req->resType = POPULATION;
			req->status = AWAITS;
			req->subject = this;
			req->type = PROVIDE;
			req->value = col;
			m_requestMap[POPULATION] = req;
		}

		if(req->value < col)
		{
			req->value = col;
		}

		//register request if it needed
		if(req->value >= MIN_HUMAN_TO_MOVE && !req->registred)
		{
			m_player->addRequest(req);
		}
	}
}


/*************************************
FUNC: foodEmigration()
DESC: Add emigration request (if it needed) and refresh number of colonists
*************************************/
void HumSettlers::foodEmigration()
{
	int population = getResources(POPULATION);
	int food = getResources(SUPPLY);
	int col = 0;
	int colToMove = 0;
	int pop25persent = 0;

	//take 12.5% of population and compare it with food storage
	col = (population >> 3);

	// take 25% of population - it is top limit for emigration
	pop25persent = (population >> 2);

	if(col > food)
	{
		colToMove = col - food;
	}

	if(colToMove > MIN_HUMAN_TO_MOVE)
	{
		Request * req = m_requestMap[POPULATION];
		if(req == nullptr)
		{
			req = new Request();
			req->resType = POPULATION;
			req->status = AWAITS;
			req->subject = this;
			req->type = PROVIDE;
			req->value = colToMove;

			m_requestMap[POPULATION] = req;
		}

		if(req->type == CONSUME)
		{
			qDebug() << "foodEmigration: Change req-direction at x:" << getMapX() << " y:" << getMapY();

			// set NOT_ACTUAL for previus request
			req->status = NOT_ACTUAL;
			req->value = 0;

			//create new request
			req = new Request();
			req->resType = POPULATION;
			req->status = AWAITS;
			req->subject = this;
			req->type = PROVIDE;
			req->value = colToMove;
			m_requestMap[POPULATION] = req;
		}

		if(req->value < colToMove)
		{
			req->value = colToMove;
		}

		if(req->value > pop25persent)
		{
			req->value = pop25persent;
		}

		//register request if it needed
		if(req->value >= MIN_HUMAN_TO_MOVE && !req->registred)
		{
			m_player->addRequest(req);
		}
	}
}
