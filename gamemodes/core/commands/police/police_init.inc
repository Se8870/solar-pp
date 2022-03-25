#if defined _inc_cmd_police
    #undef _inc_cmd_police
#endif

#if defined _inc_cmd_police_included
    #endinput
#endif

#define _inc_cmd_police_included

#include <YSI_Visual\y_commands>

// Include each command you want to use here
//#include <cmd_yourcmd>

Init_PermsPolice()
{
    // new 
    //     Group:groupPolice = GetGroupTeamId(GROUP_TEAM_POLICE);

    // Set permissions here
    // Group_SetCommand(groupPolice, YCMD:yourcmd, ALLOW);

    // print("    cmd_police... OK");
    return 1;
}
