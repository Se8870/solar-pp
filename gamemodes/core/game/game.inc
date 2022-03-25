
#if defined _inc_game
    #undef _inc_game
#endif

#if defined _INC_spp_module_game
    #endinput
#endif

#define _INC_spp_module_game

//          Name                            Value
#define     GAME_MIN_REQUIRED_PLAYERS       2

// -------------------------------------------------------------------------
// NOTE: since it's impossible to actually passing `Iterator` from function
// It will become global BUT never USE IT outside the `game` context.
#include <YSI_Data\y_foreach>
new Iterator:QueuePlayer[MAX_LOBBY]<MAX_PLAYERS>;
// -------------------------------------------------------------------------

#include <game_init>
#include <game_monitoring>
#include <game_timer>

#if !defined _inc_game_init_included
    Init_Game() return print("Module \"game.inc\"... FAIL");
#endif
