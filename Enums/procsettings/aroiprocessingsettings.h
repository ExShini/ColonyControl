#ifndef AROIPROCESSINGSETTINGS_H
#define AROIPROCESSINGSETTINGS_H

//human settlement settings:
#define AROI_MAX_HIVE_LEVEL 10 //lower level = 0, top = 10, number of levels = 11
#define AROI_MAX_MOTHERS_TOWER 4


#define MIN_AROI_TO_MOVE 100
#define AROI_MIN_RES_TO_MOVE 300

/******************************************
 *				AROI_HIVE
 *****************************************/

//next value means - how much infrastructure must be provided for achieve next settlement's level
#define AROI_HIVE_INF_LVL_0 0
#define AROI_HIVE_INF_LVL_1 80
#define AROI_HIVE_INF_LVL_2 800 + AROI_HIVE_INF_LVL_1
#define AROI_HIVE_INF_LVL_3 4500 + AROI_HIVE_INF_LVL_2
#define AROI_HIVE_INF_LVL_4 14500 + AROI_HIVE_INF_LVL_3
#define AROI_HIVE_INF_LVL_5 80000 + AROI_HIVE_INF_LVL_4
#define AROI_HIVE_INF_LVL_6 80000 + AROI_HIVE_INF_LVL_5
#define AROI_HIVE_INF_LVL_7 80000 + AROI_HIVE_INF_LVL_6
#define AROI_HIVE_INF_LVL_8 80000 + AROI_HIVE_INF_LVL_7
#define AROI_HIVE_INF_LVL_9 80000 + AROI_HIVE_INF_LVL_8
#define AROI_HIVE_INF_LVL_10 80000 + AROI_HIVE_INF_LVL_9
#define AROI_HIVE_INF_LVL_10_max 80000 + AROI_HIVE_INF_LVL_10

//next value means - how much people can live at current colony-settlement
#define AROI_HIVE_POP_LIM_0 0
#define AROI_HIVE_POP_LIM_1 1800
#define AROI_HIVE_POP_LIM_2 3000
#define AROI_HIVE_POP_LIM_3 5800
#define AROI_HIVE_POP_LIM_4 10000
#define AROI_HIVE_POP_LIM_5 22000
#define AROI_HIVE_POP_LIM_6 50000
#define AROI_HIVE_POP_LIM_7 85000
#define AROI_HIVE_POP_LIM_8 115000
#define AROI_HIVE_POP_LIM_9 175000
#define AROI_HIVE_POP_LIM_10 240000


//next value means - how much supply can be stored at current colony-settlement
#define AROI_HIVE_SUP_LIM_0 10000
#define AROI_HIVE_SUP_LIM_1 10000
#define AROI_HIVE_SUP_LIM_2 18000
#define AROI_HIVE_SUP_LIM_3 44000
#define AROI_HIVE_SUP_LIM_4 96000
#define AROI_HIVE_SUP_LIM_5 120000
#define AROI_HIVE_SUP_LIM_6 180000
#define AROI_HIVE_SUP_LIM_7 280000
#define AROI_HIVE_SUP_LIM_8 440000
#define AROI_HIVE_SUP_LIM_9 720000
#define AROI_HIVE_SUP_LIM_10 1280000



#endif // AROIPROCESSINGSETTINGS_H

