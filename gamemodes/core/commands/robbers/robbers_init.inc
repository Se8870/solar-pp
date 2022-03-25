#if defined _inc_cmd_robbers
    #undef _inc_cmd_robbers
#endif

#if defined _inc_cmd_robbers_included
    #endinput
#endif

#define _inc_cmd_robbers_included

#include <YSI_Visual\y_commands>

// Include each command you want to use here
//#include <cmd_yourcmd>

Init_PermsRobbers()
{
    // new 
    //     Group:groupRobbers = GetGroupTeamId(GROUP_TEAM_ROBBERS);

    //  Set permissions here
    // Group_SetCommand(groupRobbers, YCMD:yourcmd, ALLOW);

    // print("    cmd_robber... OK");
    return 1;
}
