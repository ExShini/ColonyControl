#ifndef OBJECTS_H
#define OBJECTS_H
#include <iostream>

#define INVALIDE_VALUE -1
#define IT_DOES_NOT_METTER -2
#define MAX_LEVEL 11	// 10 levels + 1 for top value of resource at last(10) level
#define MAX_RES_IN_ONE_SECTOR 4
#define SCIENSE_POSITION -2
#define MAIN_RACE_RES_POSITION -3

#define PERCENT_100 0
#define PERCENT_50 1
#define PERCENT_25 2
#define PERCENT_12a5 3
#define PERCENT_6a25 4

#define GROUP_FROM_32 5
#define GROUP_FROM_16 4
#define GROUP_FROM_8 3
#define GROUP_FROM_4 2
#define GROUP_FROM_2 1
#define GROUP_FROM_1 0

#define MATERIAL_COST_1 0
#define MATERIAL_COST_2 1
#define MATERIAL_COST_4 2
#define MATERIAL_COST_8 3
#define MATERIAL_COST_16 4
#define MATERIAL_COST_32 5
#define MATERIAL_COST_64 6

enum OBJECT_TYPE
{
    INVALID_OBJ_TYPE = - 1,

    t_SECTOR = 0,
    t_LAVA,
    t_DEEP_LAVA,
    t_MOUNT,

    t_MINERAL_FIELD,
    t_FERTILYTY_FIELD,

    t_DESERT,

    //human objects
    t_HUMAN_SETTLERS,
    t_HUMAN_COLONY_CENTER,
    t_HUMAN_TRANSPORT_CENTER,

    t_FIRST_UNIT,
    t_HUMAN_SHUTTLE,


    // abilities
    t_HUMAN_ION_CANON_SATELLITE,
    t_HUMAN_ION_CANON_BULLET,

    t_LAST_UNIT,




    NUM_OF_OBJ_TYPES,

    t_FIRST_OBJ = t_LAVA,

    t_FIRST_NOT_APPLICABLE_TYPE = t_LAVA,
    t_LAST_NOT_APPLICABLE_TYPE = t_MOUNT,

    t_FIRST_SECTOR_TYPE = t_SECTOR,
    t_LAST_SECTOR_TYPE = t_DESERT
};

enum RESOURSES
{
    NO_RES = INVALIDE_VALUE,

    FERTILITY = 0,
    MINERAL_WEALTH,

    POPULATION,
	SUPPLY,
    MINERALS,
    INFROSTRUCTURE,


    /***********
     * specisal parameters
     ***********/
    SHIPS,
    MAIN_RESOURSE,


    LAST_RES = INFROSTRUCTURE,
    LAST_PARAMETER = SHIPS,
    NUM_OF_RESOURSES = LAST_PARAMETER + 1,
    FIRST_RES = FERTILITY
};

enum REQ_STATUS
{
    NO_REQ_STATUS = INVALIDE_VALUE,
    AWAITS = 0,
    IN_PROGRESS,
    EXECUTED,
    NOT_ACTUAL
};

enum REQ_TYPE
{
    NO_REQ_TYPE = INVALIDE_VALUE,
    PROVIDE = 0,
    CONSUME = 1,
    NUM_OF_REQ_TYPE = 2
};

// RES container
struct Resourse
{

	Resourse(){}
	Resourse(Resourse* res)
	{
		memcpy(this, res, sizeof(Resourse));
	}

    RESOURSES type;

    // value and top limet of resourse
    int value;
    int maxValue;

	// hardLimit papameter determine how we should handle overflow of resource
    // if true - value can not be bigger whan maxValue
    // if false - value can be bigger whan maxValue, but 25% of overlaping will be last
	bool hardLimit;

    // determine size of group. Should be setuped via the power of 2 (it uses for optimization)
    int sizeOfGroup;

    // determine, who produces this resource
    // f.e POPULATION provide of manufacturing for SYPPLY
    RESOURSES producebBy;
    // it mean, how mach resourses group (of POPULATION) produce at one step
    int producedForGroup;
	// some objects is hurd to manufactoring (f.e. Units)
	// next value determine - how much work is needed for producing 1 unit of resource
	int complexityOfManufacturing;
	int currentProgress;	// current work progress

    // determine, what resource is used for producing
    RESOURSES material;
	int costOfMaterial;		// Should be setuped via the power of 2 (it uses for optimization)
    bool naturalMaterial;

    // determine, what resource is requared for supply current resource
    // for ex. POPULATION spend SYPPLY res
    RESOURSES requaredRes;
    int consumeRes;
	bool hardRequirement;	// determine - should it be destroyed if req-res is not enough

	// determine, can resourse be imported
	bool importable;
	int importLimit;	// determine res low-limit for import

	// determine, can resourse be exported
	bool exportable;
	int exportLimit;	// determine res low-limit for export

    // determine - should it be displayed in HUD
    bool displayble;
};



#endif // OBJECTS_H

