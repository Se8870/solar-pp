
#if defined _inc_user
    #undef _inc_user
#endif

#if defined _inc_user_included
    #endinput
#endif

#define _inc_database_included

#include <utils\punish_ex>
#include <YSI_Players\y_groups>

static
    Group:g_sGroupLoggedIn;

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    g_sGroupLoggedIn = Group_Create("Logged Players");
    return 1;
}

hook OnPlayerConnect(playerid)
{
    return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
    if (!Group_GetPlayer(g_sGroupLoggedIn, playerid) && !IsPlayerKicked(playerid))
    {
        SetPlayerTime(playerid, 12, 0);
        Group_SetPlayer(g_sGroupLoggedIn, playerid, true);

        TogglePlayerSpectating(playerid, true); 
        ShowLobbyInfo(playerid);
    }
    return 1;
}