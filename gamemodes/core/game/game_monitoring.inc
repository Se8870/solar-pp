
#if defined _inc_game_monitoring
    #undef _inc_game_monitoring
#endif

#if defined _inc_game_monitoring_included
    #endinput
#endif

#define _inc_game_monitoring_included

enum e_LOBBY_GAME_STATUS {
    GAME_STATUS_QUEUE,
    GAME_STATUS_PREPARING,
    GAME_STATUS_MONITORING,
    GAME_STATUS_ENDING,
};

static
    e_LOBBY_GAME_STATUS:g_sLobbyGameStatus[MAX_LOBBY char],
    bool:g_sPlayerInGame[MAX_PLAYERS char]; 

// Provide APIs
SetLobbyGameStatus(Lobby:id, e_LOBBY_GAME_STATUS:status)
{
    g_sLobbyGameStatus{id} = status;
    return 1;
}

e_LOBBY_GAME_STATUS:GetLobbyGameStatus(Lobby:id)
{
    return (g_sLobbyGameStatus{id});
}

SetPlayerInGame(playerid, bool:toggle)
{
    g_sPlayerInGame{playerid} = toggle;
}

ResetPlayerGame(playerid)
{
    if (g_sPlayerInGame{playerid} == false)
        return 0;

    g_sPlayerInGame{playerid} = false;
    ResetPlayerGroupTeam(playerid);
    return 1;
}

// This is the reason why i called "game_monitoring".
// With this below, it will try to see if a player leaving, death, etc
// and you can add many detections as you can, this is just plain basic anyway.
#include <YSI_Coding\y_hooks>
hook OnPlayerDisconnect(playerid, reason)
{
    ResetPlayerGame(playerid);
    ResetPlayerLobby(playerid);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if (ResetPlayerGame(playerid))
    {
        // Kick from the group, make them re-join the lobby
        ResetPlayerGame(playerid);
        PutPlayerInCurrentLobby(playerid);
        
        SendDeathMessage(killerid, playerid, reason);
    }
    return 1;
}
