#if defined _inc_lobby_init
    #undef _inc_lobby_init
#endif

#if defined _inc_lobby_init_included
    #endinput
#endif

#define _inc_lobby_init_included

#include <YSI_Players\y_groups>
#include <utils\common>

static
    Group:g_sLobbyLists[MAX_LOBBY char],
    Lobby:g_sPlayerCurrentLobby[MAX_PLAYERS char] = Lobby:-1;

static stock g_sPlayerLobbyName[MAX_LOBBY][MAX_LOBBY_NAME] = {
    "Archilles",
    "Athena",
    "Apollo",
    "Hades",
    "Zeus"
};

Init_Lobby()
{
    for (new Lobby:i = Lobby:0; i < MAX_LOBBY; i ++)
    {
        g_sLobbyLists{i} = Group_Create(g_sPlayerLobbyName[i]);
    }

    print("Module \"lobby.inc\"... OK");
    return 1;
}

GetLobbyName(Lobby:id, string:output[], len = MAX_LOBBY_NAME)
{
    // Check if user have any lobby joined in.
    if (id != INVALID_LOBBY_ID)
        return 0;

    strcopy(output, Group_GetName(g_sLobbyLists{id}), len);
    return 1;
}

GetPlayerLobbyCount(Lobby:id)
{
    return (Group_GetCount(g_sLobbyLists[id]));
}

Group:GetLobbyGroupId(Lobby:id)
{
    return (g_sLobbyLists[id]);
}

Lobby:GetPlayerCurrentLobby(playerid)
{
    return (g_sPlayerCurrentLobby{playerid});
}

GetCurrentLobbyName(playerid, string:output[], len = MAX_LOBBY_NAME)
{
    return GetLobbyName(g_sPlayerCurrentLobby{playerid}, output, len);
}

GetCurrentLobbyInfo(playerid, &Lobby:id, string:name[], len = MAX_LOBBY_NAME)
{
    // Check if user have any lobby joined in.
    if (g_sPlayerCurrentLobby{playerid} != INVALID_LOBBY_ID)
        return 0;

    id = g_sPlayerCurrentLobby{playerid};
    GetPlayerLobbyName(playerid, name, len);
    return 1;
}

PutPlayerInLobby(playerid, Lobby:id)
{
    // Check if user have any lobby joined in.
    if (g_sPlayerCurrentLobby{playerid} != INVALID_LOBBY_ID)
        Group_SetPlayer(g_sLobbyLists{id}, playerid, false);

    // Check if the lobby selected is full.
    if (Group_GetCount(g_sLobbyLists{id}) > MAX_PLAYER_IN_LOBBY)
        return 0;

    // If not, just set them to corresponding lobby.
    Group_SetPlayer(g_sLobbyLists{id}, playerid, true);
    g_sPlayerCurrentLobby{playerid} = id;

    // Spawn them just in case.
    SetSpawnInfo(playerid, 0, 1, 1726.18, -1641.00, 20.23, 0.0, 0, 0, 0, 0, 0, 0);
    
    SetPlayerInterior(playerid, 18);
    SetPlayerVirtualWorld(playerid, _:id + 100);

    // If there is spectating code, and the player not yet spawned
    // Just toggle it off, it'll trigger OnPlayerSpawn and SetSpawnInfo
    if (IsPlayerSpectating(playerid) && !IsPlayerSpawned(playerid))
    {
        TogglePlayerSpectating(playerid, false);
    }
    return 1;
}

PutPlayerInCurrentLobby(playerid)
{
    // Check if user have any lobby joined in.
    if (g_sPlayerCurrentLobby{playerid} == INVALID_LOBBY_ID)
        return 0;
    
    // Spawn them just in case.
    SetSpawnInfo(playerid, 0, 1, 1726.18, -1641.00, 20.23, 0.0, 0, 0, 0, 0, 0, 0);
    
    SetPlayerInterior(playerid, 18);
    SetPlayerVirtualWorld(playerid, _:g_sPlayerCurrentLobby{playerid} + 100);

    // Detects method of spawning
    if (IsPlayerSpectating(playerid))
    {
        TogglePlayerSpectating(playerid, false);
    }
    else
    {
        SpawnPlayer(playerid);
    }
    return 1;
}

ResetPlayerLobby(playerid)
{
    Group_SetPlayer(g_sLobbyLists{g_sPlayerCurrentLobby{playerid}}, playerid, false);
    return 1;
}
