
#if defined _inc_game
    #undef _inc_game
#endif

#if defined _INC_spp_module_game
    #endinput
#endif

#define _INC_spp_module_game

//          Name                            Value
#define     GAME_MIN_REQUIRED_PLAYERS       2

#include <game_init>
#include <game_monitoring>
#include <game_timer>

#if !defined _inc_game_init_included
    Init_Game() return print("Module \"game.inc\"... FAIL");
#endif
