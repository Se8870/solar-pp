#if defined _inc_cmd_general
    #undef _inc_cmd_general
#endif

#if defined _inc_cmd_general_included
    #endinput
#endif

#define _inc_cmd_general_included


// Need to make another general based command, sigh
#include <YSI_Players\y_groups>
#include <YSI_Visual\y_commands>

// Include each command you want to use here
#include <cmd_hello_world>

static
    Group:g_sGroupGeneral;

Init_PermsGeneral()
{
    g_sGroupGeneral = Group_Create("Neutral Team");

    // Set permissions here
    Group_SetCommand(g_sGroupGeneral, YCMD:hello_world, ALLOW);

    print("    cmd_general... OK");
    return 1;
}
