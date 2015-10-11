#ifndef OBJECTS_H
#define OBJECTS_H

#define INVALIDE_VALUE -1
#define IT_DOES_NOT_METTER -2
#define MAX_LEVEL 11	// 10 levels + 1 for top value of resource at last(10) level
#define MAX_RES_IN_ONE_SECTOR 4
#define SCIENSE_POSITION -2
#define MAIN_RACE_RES_POSITION -3

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
    RESOURSES type;

    // value and top limet of resourse
    int value;
    int maxValue;

    // hard papameter determine how we should handle overflow of resource
    // if true - value can not be bigger whan maxValue
    // if false - value can be bigger whan maxValue, but 25% of overlaping will be last
    bool hard;

    // determine size of group. Should be setuped via the power of 2 (it uses for optimization)
    int sizeOfGroup;

    // determine, who produces this resource
    // f.e POPULATION provide of manufacturing for SYPPLY
    RESOURSES producebBy;
    // it mean, how mach resourses group (of POPULATION) produce at one step
    int producedForGroup;

    // determine, what resource is used for producing
    RESOURSES material;
    int costOfMaterial;
    bool naturalMaterial;

    // determine, what resource is requared for supply current resource
    // for ex. POPULATION spend SYPPLY res
    RESOURSES requaredRes;
    int consumeRes;

    // determine - should it be displayed in HUD
    bool displayble;
};



#endif // OBJECTS_H

