#ifndef HUMANPROCESSINGSETTINGS
#define HUMANPROCESSINGSETTINGS

//human settlement settings:
#define HUMAN_MAX_SETTLEMENT_LEVEL 11 //10    //lower level = 1, top = 10, number of levels = 10
#define HUMAN_MAX_COLONY_CENTER_LEVEL 3
#define HUMAN_MAX_TRANSPORT_CENTER_LEVEL 2



#define MIN_HUMAN_TO_MOVE 100	// TODO: should be changed to dependency by shuttle
#define HUMAN_MIN_RES_TO_MOVE 100	// TODO: should be changed to dependency by shuttle

/******************************************
 *				HUM_SETTL
 *****************************************/

//next value means - how much infrastructure must be provided for achieve next settlement's level
#define HUM_SETTL_INF_LVL_0 0
#define HUM_SETTL_INF_LVL_1 150
#define HUM_SETTL_INF_LVL_2 1250 + HUM_SETTL_INF_LVL_1
#define HUM_SETTL_INF_LVL_3 7500 + HUM_SETTL_INF_LVL_2
#define HUM_SETTL_INF_LVL_4 26200 + HUM_SETTL_INF_LVL_3
#define HUM_SETTL_INF_LVL_5 135000 + HUM_SETTL_INF_LVL_4
#define HUM_SETTL_INF_LVL_6 135000 + HUM_SETTL_INF_LVL_5
#define HUM_SETTL_INF_LVL_7 135000 + HUM_SETTL_INF_LVL_6
#define HUM_SETTL_INF_LVL_8 135000 + HUM_SETTL_INF_LVL_7
#define HUM_SETTL_INF_LVL_9 135000 + HUM_SETTL_INF_LVL_8
#define HUM_SETTL_INF_LVL_10 135000 + HUM_SETTL_INF_LVL_9
#define HUM_SETTL_INF_LVL_10_max 135000 + HUM_SETTL_INF_LVL_10

//next value means - how much people can live at current colony-settlement
#define HUM_SETTL_POP_LIM_0 1000
#define HUM_SETTL_POP_LIM_1 2000
#define HUM_SETTL_POP_LIM_2 4000
#define HUM_SETTL_POP_LIM_3 7000
#define HUM_SETTL_POP_LIM_4 12000
#define HUM_SETTL_POP_LIM_5 20000
#define HUM_SETTL_POP_LIM_6 30000
#define HUM_SETTL_POP_LIM_7 42000
#define HUM_SETTL_POP_LIM_8 60000
#define HUM_SETTL_POP_LIM_9 100000
#define HUM_SETTL_POP_LIM_10 150000


//next value means - how much supply can be stored at current colony-settlement
#define HUM_SETTL_SUP_LIM_0 5000
#define HUM_SETTL_SUP_LIM_1 9000
#define HUM_SETTL_SUP_LIM_2 22000
#define HUM_SETTL_SUP_LIM_3 48000
#define HUM_SETTL_SUP_LIM_4 60000
#define HUM_SETTL_SUP_LIM_5 90000
#define HUM_SETTL_SUP_LIM_6 140000
#define HUM_SETTL_SUP_LIM_7 220000
#define HUM_SETTL_SUP_LIM_8 360000
#define HUM_SETTL_SUP_LIM_9 640000
#define HUM_SETTL_SUP_LIM_10 1600000



/******************************************
 *				HUM_COLONY_CENTER
 *****************************************/

//next value means - how much infrastructure must be provided for achieve next settlement's level
#define HUM_COL_CENT_INF_LVL_0 0
#define HUM_COL_CENT_INF_LVL_1 1500
#define HUM_COL_CENT_INF_LVL_2 1250 + HUM_COL_CENT_INF_LVL_1
#define HUM_COL_CENT_INF_LVL_3 7500 + HUM_COL_CENT_INF_LVL_2
#define HUM_COL_CENT_INF_LVL_4 7500 + HUM_COL_CENT_INF_LVL_3
#define HUM_COL_CENT_INF_LVL_4_max 7500 + HUM_COL_CENT_INF_LVL_4

//next value means - how much people can live at current colony-settlement
#define HUM_COL_CENT_POP_LIM_0 0
#define HUM_COL_CENT_POP_LIM_1 1000
#define HUM_COL_CENT_POP_LIM_2 2000
#define HUM_COL_CENT_POP_LIM_3 4000
#define HUM_COL_CENT_POP_LIM_4 7000


//next value means - how much supply can be stored at current colony-settlement
#define HUM_COL_CENT_SUP_LIM_0 0
#define HUM_COL_CENT_SUP_LIM_1 5000
#define HUM_COL_CENT_SUP_LIM_2 9000
#define HUM_COL_CENT_SUP_LIM_3 22000
#define HUM_COL_CENT_SUP_LIM_4 48000

//next value means - how much pioners can be started from colony center
#define HUM_COL_CENT_SHIPS_LIM_0 0
#define HUM_COL_CENT_SHIPS_LIM_1 3
#define HUM_COL_CENT_SHIPS_LIM_2 4
#define HUM_COL_CENT_SHIPS_LIM_3 5
#define HUM_COL_CENT_SHIPS_LIM_4 7


/******************************************
 *				HUM_TRANSPORT_CENTER
 *****************************************/

//next value means - how much infrastructure must be provided for achieve next settlement's level
#define HUM_TRANS_CENT_INF_LVL_0 0
#define HUM_TRANS_CENT_INF_LVL_1 1500
#define HUM_TRANS_CENT_INF_LVL_2 1250 + HUM_TRANS_CENT_INF_LVL_1
#define HUM_TRANS_CENT_INF_LVL_3 1250 + HUM_TRANS_CENT_INF_LVL_2
#define HUM_TRANS_CENT_INF_LVL_3_max 1250 + HUM_TRANS_CENT_INF_LVL_3

//next value means - how much people can live at current colony-settlement
#define HUM_TRANS_CENT_POP_LIM_0 0
#define HUM_TRANS_CENT_POP_LIM_1 800
#define HUM_TRANS_CENT_POP_LIM_2 1400
#define HUM_TRANS_CENT_POP_LIM_3 2500

//next value means - how much supply can be stored at current colony-settlement
#define HUM_TRANS_CENT_SUP_LIM_0 0
#define HUM_TRANS_CENT_SUP_LIM_1 3000
#define HUM_TRANS_CENT_SUP_LIM_2 5000
#define HUM_TRANS_CENT_SUP_LIM_3 8000

//next value means - how much pioners can be started from colony center
#define HUM_TRANS_CENT_SHIPS_LIM_0 0
#define HUM_TRANS_CENT_SHIPS_LIM_1 1
#define HUM_TRANS_CENT_SHIPS_LIM_2 2
#define HUM_TRANS_CENT_SHIPS_LIM_3 3


/******************************************
 *		END OF BUILDING SETTINGS
 *****************************************/

//human's group is 16 people
#define POPULATION_GROPS(population,groupSize) ( population >> groupSize )
#define HUMAN_FOOD_PRODUCING 19

//each people eats 1 food point
#define HUMAN_FOOD_CONSUMPTIONS(population) (population)
#define HUMAN_HUNGER_DEMAGE(food) (-(food >> 2))   //25% will die

//population growth for human = 6.25%
#define HUMAN_POPULATION_GROWTH(population) (population >> 4)

#endif // HUMANPROCESSINGSETTINGS

