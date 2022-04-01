
#if defined _inc_game
    #undef _inc_game
#endif

#if defined _INC_spp_module_game
    #endinput
#endif

#define _INC_spp_module_game

enum e_LOBBY_GAME_STATUS {
    GAME_STATUS_QUEUE,
    GAME_STATUS_PREPARING,
    GAME_STATUS_MONITORING,
    GAME_STATUS_ENDING,
};

//          Name                        Value
#define     GAME_BASE_WORLD_ID          1000 
#define     GAME_PLAYTIME               120 // 2 min

// weap config
#define     WC_USE_STREAMER             true
#define     WC_CUSTOM_VENDING_MACHINES  true

#include <game_init>
#include <game_timer>
#include <game_monitor>
#include <game_commands>

#if !defined _inc_game_init_included
    Init_Game() return print("Module \"game.inc\"... FAIL");
#endif
