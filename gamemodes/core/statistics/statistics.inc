
#if defined _inc_statistics
    #undef _inc_statistics
#endif

#if defined _INC_spp_module_statistics
    #endinput
#endif

#define _INC_spp_module_statistics

#include <statistics_init>
#include <statistics_gui>

#if !defined _inc_statistics_init_included
    Init_Statistics() return print("Module \"statistics.inc\"... FAIL");
#endif
