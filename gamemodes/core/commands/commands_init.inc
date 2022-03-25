
#if defined _inc_commands_init
    #undef _inc_commands_init
#endif

#if defined _inc_commands_init_included
    #endinput
#endif

#define _inc_commands_init_included

#include <YSI_Visual\y_commands>

// Make sure you include like this to avoid confusion
#include <commands\general\general_init>
#include <commands\police\police_init>
#include <commands\robbers\robbers_init>

Init_Commands()
{
    // Disable command by default
    Group_SetGlobalCommandDefault(UNDEF);
    print("Module \"commands.inc\"... OK");

    // Init these for permissions, will come in handy
    Init_PermsGeneral(); // aka lobby user
    Init_PermsRobbers();
    Init_PermsPolice();
    return 1;
}


