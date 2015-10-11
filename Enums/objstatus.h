#ifndef OBJSTATUS
#define OBJSTATUS

#define MAX_ACTIVE_GAME_OBJECT	3000

#define CHECK_CONDITION(condition,status)(condition & status)
#define ADD_CONDITION(condition,status)(condition|status)

#define NO_CONDITION 0				// 000000
#define NORMAL_EMPTY_CONDITION 1	// 000001
#define DESTROED_CONDITION 2	// 000010

#endif // OBJSTATUS

