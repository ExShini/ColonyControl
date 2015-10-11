#ifndef GAMEPROCESSINGSETTINGS_H
#define GAMEPROCESSINGSETTINGS_H

#include "races.h"
#include "mapsettings.h"
#include "procsettings/humanprocessingsettings.h"

#define DEFAULT_PROC_TIME_POINT 1   //1 ms time point

#define REQUEST_SECTOR_WIDTH 6
#define NUM_OF_SECTOR_AT_WIDTH ((MAP_WIDTH / REQUEST_SECTOR_WIDTH) + 1)
#define NUM_OF_SECTOR_AT_HEIGHT ((MAP_HEIGHT / REQUEST_SECTOR_WIDTH) + 1)

#define NUMBER_OF_PLAYERS 8
#define MAIN_PLAYER_ID 0




#define HUMAN_POPULATION_BASE_LIMIT 8000
#define HUMAN_POPULATION_DEMAGE(excess) (excess >> 2)   //25% will die

#endif // GAMEPROCESSINGSETTINGS_H
