
#if defined _inc_commands
    #undef _inc_commands
#endif

#if defined _INC_spp_module_commands
    #endinput
#endif

#define _INC_spp_module_commands

#tryinclude <commands_init>

#if !defined _inc_commands_init_included
    Init_Commands() return print("Module \"commands.inc\"... FAIL"), 0;
#endif