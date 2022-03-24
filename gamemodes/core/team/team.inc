
#if defined _inc_team
    #undef _inc_team
#endif

#if defined _INC_spp_module_team
    #endinput
#endif

#define _INC_spp_module_team

//          Name                    Value
#define     GROUP_TEAM_ROBBERS      1
#define     GROUP_TEAM_POLICE       2
#define     GROUP_TEAM_UNKNOWN      0

#include <team_init>

#if !defined _inc_team_init_included
    Init_Team() return print("Module \"team.inc\"... FAIL"), 0;
#endif

