/*

    Common lib to detecting things that's not available in SA:MP native code.
    Created by: Kirima2nd aka Se8870.
*/
#if defined _inc_common
    #undef _inc_common
#endif

#if defined _INC_spp_module_common_utils
    #endinput
#endif

#define _INC_spp_module_common_utils

static
    bool:g_sPlayerKicked[MAX_PLAYERS char],
    bool:g_sPlayerLoggedIn[MAX_PLAYERS char],
    bool:g_sPlayerSpectatig[MAX_PLAYERS char],
    bool:g_sPlayerSpawned[MAX_PLAYERS char];

stock bool:IsPlayerKicked(playerid)
{
    printf("Kicked? %d", g_sPlayerKicked{playerid});
    return (g_sPlayerKicked{playerid});
}

stock bool:IsPlayerLoggedIn(playerid)
{
    printf("LoggedIn? %d", g_sPlayerLoggedIn{playerid});
    return (g_sPlayerLoggedIn{playerid});
}

stock bool:IsPlayerSpectating(playerid)
{
    return (g_sPlayerSpectatig{playerid});
}

stock bool:IsPlayerSpawned(playerid)
{
    return (g_sPlayerSpawned{playerid});
}

stock SetPlayerLoggedIn(playerid, bool:toggle)
{
    g_sPlayerLoggedIn{playerid} = toggle;
    return 1;
}

// Hook for detecting "special" states that we want to capture
#include <YSI_Coding\y_hooks>
hook native Kick(playerid)
{
    g_sPlayerKicked{playerid} = true;
    return continue(playerid);
}

hook native TogglePlayerSpectating(playerid, toggle)
{
    g_sPlayerSpectatig{playerid} = bool:toggle;

    // Neat way to flip the switch *wink*
    g_sPlayerSpawned{playerid} = !bool:toggle;
    return continue(playerid, toggle);
}

hook OnPlayerSpawn(playerid)
{
    g_sPlayerSpawned{playerid} = true;
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if (newstate == PLAYER_STATE_WASTED)
    {
        g_sPlayerSpawned{playerid} = false;
        return 1;
    }

    if (newstate == PLAYER_STATE_SPAWNED)
    {
        g_sPlayerSpawned{playerid} = false;
        return 1;
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    // Reset states
    g_sPlayerKicked{playerid} = false;
    g_sPlayerLoggedIn{playerid} = false;
    g_sPlayerSpectatig{playerid} = false;
    g_sPlayerSpawned{playerid} = false;
    return 1;
}
