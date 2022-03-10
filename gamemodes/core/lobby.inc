
#if defined _inc_lobby
    #undef _inc_lobby
#endif

#if defined _inc_lobby_included
    #endinput
#endif

#define _inc_lobby_included

#if !defined MAX_LOBBY
    #define MAX_LOBBY 3
#endif

#include <YSI_Core\y_utils>
#include <YSI_Players\y_groups>
#include <YSI_Visual\y_dialog>

#include <teams>

static
    Group:g_sPlayerLobbys[MAX_LOBBY],
    g_sPlayerCurrentLobby[MAX_PLAYERS];

static const gsc_arrLobbyName[MAX_LOBBY][] = {
    "Athena",
    "Poseidon",
    "Apollo"
};

JoinLobby(playerid, lobbyid)
{
    SetSpawnInfo(playerid, 1, 300, 246.40, 110.84, 1003.22, 90.0, 0, 0, 0, 0, 0, 0);
    TogglePlayerSpectating(playerid, false);

    Group_SetPlayer(g_sPlayerLobbys[lobbyid], playerid, true);
    printf("Joining lobby %d", lobbyid);

    g_sPlayerCurrentLobby[playerid] = lobbyid;
    return 1;
}

ShowLobbyInfo(playerid)
{
    new lobbyList[128];
    format(lobbyList, sizeof(lobbyList), "Lobby Name\tPlayers\n");

	foreach (new Group:g : CreatedGroup())
	{
        if (!strcmp(Group_GetName(g), "Lobby", false, 5))
        {
            format(lobbyList, sizeof(lobbyList), "%s%s\t%d\n", lobbyList, Group_GetName(g), Group_GetCount(g));
        }
	}

    inline Lobby_OnResponse(response, listitem, string:inputtext[])
    {
        #pragma unused inputtext
        if (!response)
        {
            KickPlayer(playerid);
            return;
        }

        JoinLobby(playerid, listitem);
    }

    Dialog_ShowCallback(playerid, using inline Lobby_OnResponse, DIALOG_STYLE_TABLIST_HEADERS, "Solarize Police Pursuit - Select Lobby", lobbyList, "Join", "");
}

SetPlayerLobbyStatus(playerid, bool:toggle)
{
    g_sPlayerLobbyStatus[playerid] = toggle;
    return 1;
}

PutPlayerInLobbyMenu(playerid)
{
    TogglePlayerSpectating(playerid, true);
    
    new currentLobby = g_sPlayerCurrentLobby[playerid];
    Group_SetPlayer(g_sPlayerLobbys[currentLobby], playerid, false);

    printf("Leaving lobby %d", currentLobby);
    g_sPlayerCurrentLobby[playerid] = -1;

    ShowLobbyInfo(playerid);
    return 1;
}

GetLobbyInfo(lobbyid, string:name[], &residents)
{
    strcopy(name, Group_GetName(g_sPlayerLobbys[lobbyid]), 32);
    residents = Group_GetCount(g_sPlayerLobbys[lobbyid]);
    return 1;
}

CountPlayerInLobby(lobbyid)
{
    return (Group_GetCount(g_sPlayerLobbys[lobbyid]));
}

// Internal functions, kinda.
Group:GetLobbyGroupId(lobbyid)
{
    return (g_sPlayerLobbys[lobbyid]);
}

GetPlayerLobbyInfo(playerid, string:name[], &lobbyid, &residents)
{
    new currentLobby = g_sPlayerCurrentLobby[playerid];

    if (currentLobby == -1)
        return 0;
    
    lobbyid = currentLobby;
    GetLobbyInfo(currentLobby, name, residents);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnGameModeInit()
{
    for (new i; i < MAX_LOBBY; i ++)
    {
        g_sPlayerLobbys[i] = Group_Create(va_return("Lobby %s", gsc_arrLobbyName[i]));
    }
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    SetPlayerInterior(playerid, 10);
    SetPlayerVirtualWorld(playerid, g_sPlayerCurrentLobby[playerid] + 100);

    JoinTeam(playerid, TEAM_NEUTRAL);
    return 1;
}