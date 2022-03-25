
#if defined _inc_lobby
    #undef _inc_lobby
#endif

#if defined _INC_spp_module_lobby
    #endinput
#endif

#define _INC_spp_module_lobby

//          Name                    Value
#define     MAX_LOBBY               Lobby:5
#define     INVALID_LOBBY_ID        Lobby:-1
#define     MAX_PLAYER_IN_LOBBY     12
#define     MAX_LOBBY_NAME          16 + 1

#include <lobby_init>
#include <lobby_gui>
#include <lobby_msg>

#if !defined _inc_lobby_init_included
    Init_Lobby() return print("Module \"lobby.inc\"... FAIL");
#endif
