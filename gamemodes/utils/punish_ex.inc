#if defined _inc_punish_ex
    #undef _inc_punish_ex
#endif

#if defined _inc_punish_ex_included
    #endinput
#endif

#define _inc_punish_ex_included

#include <YSI_Extra\y_inline_timers>

static
    g_sPlayerKicked[MAX_PLAYERS];

stock IsPlayerKicked(playerid)
{
    return (g_sPlayerKicked[playerid]);
}

stock KickPlayer(playerid)
{
    inline OnKicked()
    {
        g_sPlayerKicked[playerid] = 1;
        Kick(playerid);
    }

    Timer_CreateCallback(using inline OnKicked, 1000, 1);
}
